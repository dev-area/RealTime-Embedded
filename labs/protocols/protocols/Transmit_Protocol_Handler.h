
#ifndef TRANSMIT_PROTOCOL_HANDLER_H
#define TRANSMIT_PROTOCOL_HANDLER_H

#include "Retransmission_Buffer.h"
#include "Packet_Queue.h"


class Transmit_Protocol_Handler
{
    enum {L2_HEADER_LENGTH=8};

    int m_next_Transmit_Sequence_Number;

    int m_next_Receive_Sequence_Number;

    Retransmission_Buffer m_retransmission_Buffer;

    Packet_Queue<Datagram> m_transmit_Queue;

    Protocol_Layer *m_p_Layer;


    void Transmit_Packet(Datagram *p_Packet)
    {
        // Add header and sequence numbers
        p_Packet->Add_Header(L2_HEADER_LENGTH);

        p_Packet->Set_Receive_Sequence_Number(m_next_Receive_Sequence_Number);

        // Fill the transmit sequence number and inform
        // retransmission queue if the packet is not
        // an acknowledgement packet
        if (p_Packet->GetType() != Datagram::ACKNOWLEDGEMENT)
        {
            p_Packet->Set_Transmit_Sequence_Number(m_next_Transmit_Sequence_Number);
            Modulo_Increment(m_next_Transmit_Sequence_Number);
            // Inform retransmission queue about the packet
            m_retransmission_Buffer.Add_Packet(p_Packet);
        }

        // Pass on the message for transmission to the lower layer. A pointer to the lower
        // layer is obtained from the parent layer.
        Protocol_Layer *p_Lower_Layer = m_p_Layer->Get_Lower_Layer();
        if (p_Lower_Layer)
        {
            p_Lower_Layer->Transmit(p_Packet);
        }
    }

public:   


    Transmit_Protocol_Handler(Protocol_Layer *p_Layer) :
      m_p_Layer(p_Layer), m_retransmission_Buffer(p_Layer)
      {
      }


      void Handle_Transmit_Request(Datagram *p_Packet)
      {
          // Check for space in window
          if (m_retransmission_Buffer.Get_Window_Room() == 0)
          {
              // No space, window is full. The message waits
              // in the queue
              m_transmit_Queue.Add(p_Packet);
          }
          else
          {
              // If the window is open, transmit packet immediately
              Transmit_Packet(p_Packet);
          } 
      }


      void Handle_Send_Ack_Request(int new_Receive_Sequence_Number)
      {
          // Copy the new receive sequence number
          // to acknowledge a packet
          m_next_Receive_Sequence_Number = new_Receive_Sequence_Number;

          // If there are no more pending messages,
          // send an explicit acknowledgement message. If messages
          // are pending, ack can be piggy backed.
          if (m_transmit_Queue.Get_Length() == 0)
          {
              // No messages are pending transmission.
              // Send explicit ack
              Transmit_Packet(new Datagram(Datagram::ACKNOWLEDGEMENT));
          }
      }


      void Handle_Received_Ack_Notification(int acknowledged_Sequence_Number)
      {
          Datagram *p_Packet;

          // Delegate ack processing to Retransmission Buffer
          m_retransmission_Buffer.Handle_Received_Ack_Notification(acknowledged_Sequence_Number);

          // Check if the transmit window has opened up. If there is is room in
          // the window, transmit packets waiting in the transmit queue
          int windowRoom = m_retransmission_Buffer.Get_Window_Room();
          for (int i=0; i < windowRoom && m_transmit_Queue.Get_Length(); i++)
          {
              p_Packet = m_transmit_Queue.Remove();
              Transmit_Packet(p_Packet);
          }
      }

};
#endif

