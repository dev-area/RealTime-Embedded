#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H

#include <queue>           // STL header file for queue
#include <list>
using namespace std;       // Specify that we are using the std namespace


template <typename Packet> 
class Packet_Queue
{
   typedef queue<Packet *, list<Packet *> > Packet_Queue_Type;

   Packet_Queue_Type m_packet_Queue;
      
public:
   void Add(Packet *p_Packet);
   Packet *Remove();
   size_t Get_Length() const;
};
#endif
