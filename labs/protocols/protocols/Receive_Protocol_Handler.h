#include "Transmit_Protocol_Handler.h"


class Receive_Protocol_Handler
{
    enum {L2_HEADER_LENGTH=8};

    int m_next_Expected_Sequence_Number;

    int m_last_Acknowledged_Sequence_Number;

    Transmit_Protocol_Handler *m_p_Transmit_Protocol_Handler;

    Protocol_Layer *m_p_Layer;

public:   


    void Handle_Received_Packet(Datagram *p_Packet)
    {
        // Extract the header needed by this layer
        p_Packet->Extract_Header(L2_HEADER_LENGTH);

        // Compare the packet's transmit sequence number with 
        // the expected sequence number
        if (p_Packet->Get_Transmit_Sequence_Number() == m_next_Expected_Sequence_Number)
        {  
            // Request Transmit Sequence Handler to acknowledge 
            // the just received packet
            m_p_Transmit_Protocol_Handler->Handle_Send_Ack_Request(m_next_Expected_Sequence_Number);

            // Pass the message to the higher layer. The message is passed only if the upper layer
            // has been specified.
            Protocol_Layer *p_Upper_Layer = m_p_Layer->Get_Upper_Layer();
            if (p_Upper_Layer)
            {
                p_Upper_Layer->Handle_Receive(p_Packet);
            }

            // Modulo increment the next expected sequence number
            Modulo_Increment(m_next_Expected_Sequence_Number);
        }

        // Compare the packet's receive sequence number with the 
        // last acknowledged sequence number. (Change in sequence number 
        // implies that an acknowledgement has been received from the other end)
        if (p_Packet->Get_Receive_Sequence_Number() != m_last_Acknowledged_Sequence_Number)
        {
            // Update the last acknowledged sequence number
            m_last_Acknowledged_Sequence_Number = p_Packet->Get_Receive_Sequence_Number();

            // Inform the Transmit Protocol Handler about the 
            // acknowledgements received from the other end
            m_p_Transmit_Protocol_Handler->Handle_Received_Ack_Notification(
                m_last_Acknowledged_Sequence_Number);      
        }
    }


    Receive_Protocol_Handler(Protocol_Layer *p_Layer) :
    m_p_Layer(p_Layer)
    {
    }
};
