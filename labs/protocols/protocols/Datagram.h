#ifndef DATAGRAM_H
#define DATAGRAM_H
#include "Protocol_Packet.h"

class Datagram : public Protocol_Packet
{
public:

    enum Type {ACKNOWLEDGEMENT, DATAGRAM};

    Datagram(const Datagram *p_Packet);
    Datagram(Type type);
    int Get_Receive_Sequence_Number() const;
    int Get_Transmit_Sequence_Number() const;
    void Set_Receive_Sequence_Number(int sequence_Number);
    void Set_Transmit_Sequence_Number(int sequence_Number);
    Type GetType() const;
};
#endif

