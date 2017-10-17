/************************************************************/
/* PROJECT NAME: Vectored Interrupt                         */
/* Project:      LPC2100 Training course                    */
/* Engineer:     T Martin      tmartin@hitex.co.uk          */
/* Filename:     main.c                                     */
/* Language:     C                      	                */
/* Compiler:     Keil RealView 2.50a	                    */
/* Assembler:    				                            */
/*                                                          */
/************************************************************/
/* COPYRIGHT: Hitex UK Ltd 		2005						*/
/* LICENSE:   THIS VERSION CREATED FOR FREE DISTRIBUTION	*/
/************************************************************/
/* Function:                                                */
/*                                                          */
/* Example configuration of VIC for vectored interrupt  	*/
/*															*/
/* Demonstrates serving the external interrupt as a 		*/ 
/* vectored interrupt										*/
/*															*/	
/* Oscillator frequency 12.000 Mhz							*/
/* Target board Keil MCB2100								*/
/************************************************************/

// pattern taken from www.embedded.com

#include <LPC21xx.H>

#define OUTSIDE_INTERRUPT_NUMBER 0
#define TIMER_INTERRUPT_NUMBER 1
//

#define MAX_INTERRUPTS 15

class Interrupt 
{
 public:
  	Interrupt(void){}
  	static void Register(int interrupt_number, Interrupt* intThisPtr)
  	{
  		ISRVectorTable[interrupt_number] = intThisPtr;
  	}
	static void Interrupt_0(void) __irq; // processor’s interrupt vector table set
	static void Interrupt_1(void) __irq; // to point to these functions
	static void Interrupt_2(void) __irq;

	virtual void ISR(void) = 0;
private: // Array of pointer to objects inheriting from interrupt

	static Interrupt* ISRVectorTable[MAX_INTERRUPTS];
};

Interrupt* Interrupt::ISRVectorTable[MAX_INTERRUPTS];

void Interrupt::Interrupt_0(void) __irq
{
	ISRVectorTable[0]->ISR();
}

void Interrupt::Interrupt_1(void) __irq
{
	ISRVectorTable[1]->ISR();
}
void Interrupt::Interrupt_2(void) __irq
{
	ISRVectorTable[2]->ISR();
}

class OutsideInterrupt : public Interrupt
{
public:
  OutsideInterrupt()
  {
  	someObjectState = 0;
  	Interrupt::Register(OUTSIDE_INTERRUPT_NUMBER, this); 
  }
  virtual void ISR(void)
  {
		if(someObjectState++ < 4)
			IOSET1 			= 0x00FF0000;						//Set the LED pins
		else
			IOCLR1 = 0x00FF0000;
	
		EXTINT  		= 0x00000002;						//Clear the peripheral interrupt flag
		VICVectAddr 	= 0x00000000;						//Dummy write to signal end of interrupt
		if(someObjectState==8) 
			someObjectState=0;  	
  }

private:
	int someObjectState;
};

OutsideInterrupt global;

void initInterruptVector()
{

	IODIR1			= 0x00FF0000;						//Set the LED pins as outputs
	IOCLR1			= 0x00FF0000;						//Clear the LED pins
	PINSEL0 		= 0x20000000;						//Enable the EXTINT1 interrupt
	VICVectCntl0 	= 0x0000002F;  							//select a priority slot for a given interrupt
	VICVectAddr0 	= (unsigned)(Interrupt::Interrupt_0);	//pass the address of the IRQ into the VIC slot	  
	VICIntEnable 	= 0x00008000;						//enable interrupt

}


int main (void)
{
   initInterruptVector();
	while(1)
	{
		;													//Idle
	}
}

