#ifndef PROTOCOL_PACKET_H
#define PROTOCOL_PACKET_H

class Protocol_Packet
{
    enum { MAXIMUM_PACKET_LENGTH = 1500};
    struct Region
    {
        int offset;
        int length;
    };
    Region m_header;
    Region m_body;
    Region m_trailer;
    char m_buffer[MAXIMUM_PACKET_LENGTH];
public:
    Protocol_Packet(int body_Length, int body_Offset);
	void Add_Header(int length);
    void Add_Trailer(int length);
    void Extract_Header(int length);
    void Extract_Trailer(int length);
    char *Get_Header();
    char *Get_Body();
    char *Get_Trailer();
    int Get_Length();
};

#endif
