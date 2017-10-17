#include "Packet_Queue.h"

template <typename Packet> 
void Packet_Queue<Packet>::Add(Packet *p_Packet)
{
  // Insert the element at the end of the queue
  m_packet_Queue.push(p_Packet);
}

template <typename Packet> 
Packet *Packet_Queue<Packet>::Remove()
{
  Packet *p_Packet = NULL;
  
  // Check if the message queue is not empty
  if (!m_packet_Queue.empty())
  {
     // Queue is not empty so get a pointer to the
     // first message in the queue
     p_Packet = m_packet_Queue.front();
     
     // Now remove the pointer from the message queue
     m_packet_Queue.pop();
  }
  return p_Packet;
}

template <typename Packet> 
size_t Packet_Queue<Packet>::Get_Length() const
{
  return m_packet_Queue.size();
}   
