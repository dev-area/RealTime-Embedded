#ifndef DATALINK_LAYER_H
#define DATALINK_LAYER_H

#include "Protocol_Layer.h"
#include "Transmit_Protocol_Handler.h"
#include "Receive_Protocol_Handler.h"

class Protocol_Packet;


class Datalink_Layer : public Protocol_Layer
{
    Transmit_Protocol_Handler m_transmit_Protocol_Handler;

    Receive_Protocol_Handler m_receive_Protocol_Handler;

public:

    Datalink_Layer();

   // Process and transmit the packet passed by higher layer.
   void Transmit(Protocol_Packet *p_Packet);

   void Handle_Receive(Protocol_Packet *p_Packet);

};

#endif
