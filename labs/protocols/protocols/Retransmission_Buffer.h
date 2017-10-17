
#ifndef RETRANSMISSION_BUFFER_H
#define RETRANSMISSION_BUFFER_H

#include "Datagram.h"
#include "Protocol_Layer.h"

int Modulo_Increment(int& i);
int Modulo_Difference(int seq_1, int seq_2);
int Modulo_Add(int seq_1, int seq_2);


class Retransmission_Buffer
{
    enum { WINDOW_SIZE = 512 };

    Datagram *m_p_Pending_Packets[WINDOW_SIZE];
    int m_last_Transmitted_Sequence_Number;
    int m_last_Acknowledged_Sequence_Number;
    Protocol_Layer *m_p_Layer;

    void Restart_Await_Ack_Timer();
    void Stop_Await_Ack_Timer();

public:


    Retransmission_Buffer(Protocol_Layer *p_Layer) : m_p_Layer(p_Layer)
    {
    }


    void Add_Packet(const Datagram *p_Packet)
    {
    
       m_last_Transmitted_Sequence_Number = p_Packet->Get_Transmit_Sequence_Number();
       
       // Make a copy of the packet for the retransmission buffer
       m_p_Pending_Packets[m_last_Transmitted_Sequence_Number] = new Datagram(p_Packet);

       // Restart the ack timer. Timer is started if its not running
       Restart_Await_Ack_Timer();       
    }
    

    void Handle_Received_Ack_Notification(int new_Acknowledged_Sequence_Number)
    {
        // Delete the buffers allocted to retransmission buffers 
        // for all allocated packets.
        for (int i=m_last_Acknowledged_Sequence_Number; i != new_Acknowledged_Sequence_Number; 
                                                     Modulo_Increment(i))
        {
           delete m_p_Pending_Packets[i];
           m_p_Pending_Packets[i] = NULL; 
        }
        
        // Save the new sequence number as the last acknowledged seq num
        m_last_Acknowledged_Sequence_Number = new_Acknowledged_Sequence_Number;
        
        // If all packets have been acknowledged, stop timer
        if (m_last_Transmitted_Sequence_Number == m_last_Acknowledged_Sequence_Number)
        {
           Stop_Await_Ack_Timer();
        } 
    }
    

    int Get_Window_Room() const
    {
       // Return the room in window by determining the current count of messages
       // awaiting acknowledgement
       return (WINDOW_SIZE - 
           Modulo_Difference(m_last_Transmitted_Sequence_Number, m_last_Acknowledged_Sequence_Number));
    }

    void Handle_Await_Ack_Timeout()
    {       
        Datagram *p_Packet;

        // Initiate retransmission of all unacknowledged packets by 
        // looping from the last unacknowledged sequence number to 
        // the sequence number of the last transmitted message
        for (int i=Modulo_Add(m_last_Acknowledged_Sequence_Number, 1); 
             i != m_last_Transmitted_Sequence_Number; Modulo_Increment(i))
        { 

           // Get the packet corresponding to the sequence number i
           p_Packet = m_p_Pending_Packets[i];

           // Pass on the message for transmission on the serial port
           (m_p_Layer->Get_Lower_Layer())->Transmit(p_Packet);                
        }
        
        // Now restart the timer
        Restart_Await_Ack_Timer();
    }
};
#endif
