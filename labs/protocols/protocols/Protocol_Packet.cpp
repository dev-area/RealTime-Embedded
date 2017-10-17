#include "Protocol_Packet.h"

Protocol_Packet::Protocol_Packet(int body_Length, int body_Offset)
{
    m_header.length = 0;
    m_trailer.length = 0;
    m_body.offset = body_Offset;
    m_body.length = body_Length;
}

void Protocol_Packet::Add_Header(int length)
{
    // Consider the header of the higher layer to be a part of
    // the body for the this layer.
    m_body.offset -= m_header.length;
    m_body.length += m_header.length;

    // Save the length and header offset of the new layer. Addition
    // of the header would move up the header offset.
    m_header.length = length;
    m_header.offset = m_body.offset - length;      
}

void Protocol_Packet::Add_Trailer(int length)
{
    // Consider the trailer of the higher layer to be a part of
    // the body of this layer.
    m_body.length += m_trailer.length;

    // Now add the trailer at the end of the updated body.
    m_trailer.length = length;
    m_trailer.offset = m_body.offset + m_body.length;
}

void Protocol_Packet::Extract_Header(int length)
{
    // Update the new header. The header begins at current
    // body start offset.
    m_header.offset = m_body.offset;
    m_header.length = length;

    // Reduce the body size to account for the removed header.
    m_body.offset += length;
    m_body.length -= length;
}


void Protocol_Packet::Extract_Trailer(int length)
{
    // Reduce the length to adjust for the extracted trailer.
    m_body.length -= length;

    // Setup the trailer to start at the end of the body.
    m_trailer.offset = m_body.offset + m_body.length;
    m_trailer.length = length;
}

char *Protocol_Packet::Get_Header()
{
    return (&m_buffer[m_header.offset]);
}

char *Protocol_Packet::Get_Body()
{
    return (&m_buffer[m_body.offset]);
}

char *Protocol_Packet::Get_Trailer()
{
    return (&m_buffer[m_trailer.offset]);
}

int Protocol_Packet::Get_Length()
{
    return (m_header.length + m_body.length + m_trailer.length);
}
