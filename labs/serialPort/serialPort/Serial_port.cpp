const int BUFFER_SIZE = 255;
class Queue;
class Message;

class SerialPort
{
   // Queues for receiving and transmitting messages
   Queue *m_pReceiveQueue;
   Queue *m_pTransmitQueue;
   
   // Common Buffer structure for Transmit and Receive Buffers
   struct Buffer
   { 
      int currentIndex;
      char length;
      char data[BUFFER_SIZE];
   };
   
   // Buffers used for store data when the ISR is receiving or transmitting data
   Buffer m_receiveBuffer;
   Buffer m_transmitBuffer;
   
   // Addresses for device registers
   const long m_interruptStatusRegister;    // Register to manage interrupts
   const long m_transmitDataRegister;       // Register to copy data to be transmitted
   const long m_receiveDataRegister;        // Register to obtain received data
   
   const int m_portId;                      // Id assigned to this serial port
   
   // Interrupt handlers
   void HandleRxInterrupt();
   void HandleTxInterrupt(); 

public:
   SerialPort(long baseAddr, int portId, Queue *pTxQueue, Queue *pRxQueue) 
                             : m_interruptStatusRegister(baseAddr),
                               m_transmitDataRegister(baseAddr+1),
                               m_receiveDataRegister(baseAddr+2),
                               m_portId(portId)
   {
      m_receiveBuffer.length = 0;
      m_receiveBuffer.currentIndex = 0;
      m_transmitBuffer.length = 0;
      m_transmitBuffer.currentIndex = 0;
      // Note: Receive interrupt is always enabled, as data can be received
      //       at any time. Transmit interrupt is enabled only when transmitting
      //       data on the serial link.
      io_write(m_interruptStatusRegister, ENABLE_RX_DISABLE_TX_MASK);
      
      // Initialize pointers to associated queues
      m_pTransmitQueue = pTxQueue;
      m_pReceiveQueue = pRxQueue;
   }
   
   ~SerialPort()
   {
      io_write(m_interruptStatusRegister, DISABLE_RX_DISABLE_TX_MASK);
   }

   // Event Handler that is invoked when the ISR has finished transmitting
   // a message
   void HandleTransmissionComplete();
   
   // Event Handler that is invoked when the ISR has received a new message
   void HandleReceiveComplete();
   
   // This handler is invoked by higher layers when they wish to transmit
   // a message over the serial link
   void HandleTxMessage(Message *pMsg)
   {
      // Add the message to the transmit queue
      m_pTransmitQueue->Write(pMsg);
      
      // Check if this is the first message. If so start transmission
      // for the data by preparing the transmit buffer
      // (Accomplished by calling HandleTransmissionComplete())
      // Also enable the transmit interrupt as new data is available
      // for transmission.
      if (m_pTransmitQueue->GetLength() == 1)
      {
         HandleTransmissionComplete();         
         io_write(interruptStatusRegister, ENABLE_RX_ENABLE_TX); 
      }
   }
   
   // Check the interrupt status register to determine if some
   // interrupt is pending
   bool IsInterruptPending()
   {   
      int interruptStatus = io_read(m_interruptStatusRegisterAddress);
      return (interruptStatus & PENDING_INTERRUPT_BIT);
   }
   
   // This method is executed from the ISR. It checks the interrupt
   // status register to determine the exact source of interrupt.
   void HandleInterrupt()
   { 
      int interruptStatus = io_read(m_interruptStatusRegisterAddress);
      
      if (interruptStatus & RECEIVED_DATA_BIT)
      {
         HandleRxInterrupt();
      }
      else if (interruptStatus & TRANSMITTER_EMPTY_BIT)
      {
         HandleTxInterrupt();
      }
      else
      {
         m_spuriousInterruptCounter++;
      }      
   } 
};

// Called when the ISR has finished processing the
// current message and it is ready to process another one.
void SerialPort::HandleTransmissionComplete()
{
   Message *pMsg;
   
   // Check for more messages to transmit
   pMsg = m_pTransmitQueue->Read();
   
   if (pMsg)
   {
       // Message found for transmission, set up the transmit
       // buffer
       m_transmitBuffer.length = pMsg->length;
       m_transmitBuffer.currentIndex = 0;
       
       // Copying data for tranmisson
       memcpy(m_transmitBuffer.data, pMsg, pMsg->length);
   }
   else  
   {
       // No more messages pending for transmission, so disable the
       // transmit interrupt.
       io_write(m_interruptStatusRegister, ENABLE_RX_DISABLE_TX_MASK); 
   }   
}

// Called when ISR has received a complete message
void SerialPort::HandleReceiveComplete()
{
   // Allocate a buffer for the message and copy the contents
   // from the receive buffer
   Message *pMsg = new Message;
   memcpy(pMsg, m_receiveBuffer.data, m_receiveBuffer.length);
   // Copy the length of the message
   pMsg->length = m_receiveBuffer.length;  
   // Pass the message to the higher layers
   m_pReceiveQueue->Write(pMsg);
   
   // Cleanup the message buffer for receiving the next message
   m_receiveBuffer.currentIndex = 0;   
}

// Receive interrupt handler
void SerialPort::HandleRxInterrupt()
{
    int data;
    
    // Read the received byte from the device
    data = io_read(m_receiveDataRegister);
    
    // Check if this is the first byte. The first
    // byte contains the total length of the message
    if (m_receiveBuffer.currentIndex == 0)
    {
       m_receiveBuffer.length = data;
    }
    
    // Copy the bytes into the receive buffer
    m_receiveBuffer.data[m_receiveBuffer.currentIndex++] = data;
    
    // Check if the complete message has been received, if so
    // raise an event to notify the protocol task.
    if (m_receiveBuffer.currentIndex == m_receiveBuffer.length)
    {
       send_event(RECEIVE_COMPLETE, m_portId);
    }    
}

// Transmit Interrupt Handler
void SerialPort::HandleTxInterrupt()
{
   // Get the byte to be transmitted
   char data = 
       m_transmitBuffer.data[m_transmitBuffer.currentIndex++];
   
   // Write the byte to the transmit register    
   io_write(m_transmitDataRegister, data);
   
   // Check if the complete message has been transmitted, if so
   // raise an event to notify the protocol task
   if (m_transmitBuffer.currentIndex == m_transmitBuffer.length)
   {
      send_event(TRANSMISSION_COMPLETE, m_portId);
   }
}

