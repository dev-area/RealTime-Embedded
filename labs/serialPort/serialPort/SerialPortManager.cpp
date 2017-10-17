// Manager all the serial ports on the board    
class SerialPortManager
{
   // Array of serial ports (declared static, as it is accessed
   // from the ISR)
   static SerialPort m_serialPort[MAX_SERIAL_PORTS];
   
public:
   // Interrupt Handler. (Needs to be static as ISRs should be
   // regular functions with C calling conventions. Methods cannot be
   // declared ISRs)
   static void InterruptServiceRoutine();
   
   SerialPortManager()
   {
       // Install the interrupt handler on start up
       install_interrupt_handler(SERIAL_PORT_ISR, InterruptServiceRoutine);
   }
   
   ~SerialPortManager()
   {
       // Deinstall the handler when exiting
       deinstall_interrupt_handler(SERIAL_PORT_ISR);
   }
   
   // Called when the ISR generates an event. This method dispatches
   // the event to the appropriate serial port object
   void HandleInterruptEvent(const Event *pEvent)
   {
       SerialPort *pPort;       
       pPort = m_serialPort[pEvent->portId];
       
       switch (pEvent->type)
       {
       case TRANSMISSION_COMPLETE:
            pPort->HandleTransmissionComplete();
            break;
            
       case RECEIVE_COMPLETE:
            pPort->HandleReceiveComplete();
            break;
       }
   }   
};

// Static declaration
SerialPort SerialPortManager::m_serialPort[MAX_SERIAL_PORTS];

// Interrupt Service Routine for all interrupts
void SerialPortManager::InterruptServiceRoutine()
{
   bool foundInterruptSource = false;
   
   // Loop through all the serial ports to find out which serial device
   // generated this interrupt. (Multiple device interrupts might be
   // generated at the same time)
   for (i=0; i < MAX_SERIAL_PORTS; i++)
   {
      if (m_serialPort[i].IsInterruptPending())
      {
         foundInterruptSource = true;
         m_serialPort[i].HandleInterrupt();
      }
   }
   
   // Interrupt was raised but no device was found with a pending
   // interrupt. Raise the spurious interrupt counter
   if (!foundInterruptSource)
   {
      m_spuriousInterruptCount++;
   } 
}

