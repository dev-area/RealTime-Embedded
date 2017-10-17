#ifndef PROTOCOL_LAYER_H
#define PROTOCOL_LAYER_H

#include <stdio.h>
class Protocol_Packet;


class Protocol_Layer
{
    Protocol_Layer *m_p_Lower_Layer;

    Protocol_Layer *m_p_Upper_Layer;

public:
    Protocol_Layer()
    {
        m_p_Lower_Layer = NULL;
        m_p_Upper_Layer = NULL;
    }

    virtual void Transmit(Protocol_Packet *p_Packet) = 0;

    virtual void Handle_Receive(Protocol_Packet *p_Packet) = 0;

    void Set_Upper_Layer(Protocol_Layer *p_Layer)
    {   m_p_Upper_Layer = p_Layer; }


    void Set_Lower_Layer(Protocol_Layer *p_Layer)
    {   m_p_Lower_Layer = p_Layer; }


    Protocol_Layer *Get_Upper_Layer() const
    {   return m_p_Upper_Layer; }


    Protocol_Layer *Get_Lower_Layer() const
    {   return m_p_Lower_Layer; }

};
#endif
