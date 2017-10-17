#ifndef PROTOCOL_STACK_H
#define PROTOCOL_STACK_H

#include <stdio.h>

class Protocol_Packet;
class Protocol_Layer;


class Protocol_Stack
{
public:

    enum Placement
    {
        TOP,  
        ABOVE,
        BELOW
    };

    void Handle_Transmit(Protocol_Packet *p_Packet);
    void Handle_Receive(Protocol_Packet *p_Packet);

    void Add_Layer(Protocol_Layer *p_Layer, Placement placement = TOP, Protocol_Layer *p_Existing_Layer = NULL);
    void Remove_Layer(Protocol_Layer *p_Layer);

    Protocol_Stack();

private:

    Protocol_Layer *m_p_Highest_Layer;

    Protocol_Layer *m_p_Lowest_Layer;
};
#endif
