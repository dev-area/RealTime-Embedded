


#include <intrinsics.h>

#define STOP_BIT_SELECT_bit    0x2   // Stop bit control in UxLCR is bit 2

#define ENABLE_UART1_RX     0x12
#define ENABLE_UART1_TX     0x10

#define MAX_SOFTWARE_TIMERS 3

#define SetBit(x,y);       ( (x) |= (1<<y) )
#define ClrBit(x,y);       ( (x) &= (~(1<<y)) )

typedef struct
{
  unsigned int us_Ticks;
  unsigned int us_Event;
} SoftwareTimer_t;

SoftwareTimer_t  softTimer[MAX_SOFTWARE_TIMERS];
char textString[] = "For cool ARM C/EC++development tools call Mark at IAR 508 485 2692";

int main(void);
void initializeInterruptDataStructs(void);
void installTimer(SoftwareTimer_t *, unsigned int, unsigned int , unsigned int);

__irq __arm void IRQ_ISR_Handler (void);
void MM_TIMER0_ISR();
void NonVectISR(void);
void sendByte(char byte);
void feed(void);




