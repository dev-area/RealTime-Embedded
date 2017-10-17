#include "Datalink_Layer.h"
#include "Protocol_Packet.h"


Datalink_Layer::Datalink_Layer() : 
                    m_transmit_Protocol_Handler(this),
                    m_receive_Protocol_Handler(this)
{ }


void Datalink_Layer::Transmit(Protocol_Packet *p_Packet)
{
    m_transmit_Protocol_Handler.Handle_Transmit_Request((Datagram *)p_Packet);
}


void Datalink_Layer::Handle_Receive(Protocol_Packet *p_Packet)
{
    m_receive_Protocol_Handler.Handle_Received_Packet((Datagram *)p_Packet);
}
