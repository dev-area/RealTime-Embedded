#include <NXP/iolpc2148.h>
/*************************************************************************
 * Function Name: irq_handler
 * Parameters: void
 * Return: void
 *
 * Description: IRQ subroutine
* Note: This is ARM mode code - full 32 bit code	
 *************************************************************************/
__irq __arm void irq_handler (void)
{
  void (*interrupt_function)();
  unsigned int vector;

  vector = VICVectAddr;     // Get interrupt vector.
  interrupt_function = (void(*)())vector;
  (*interrupt_function)();  // Call vectored interrupt function thru pointer
  VICVectAddr = 0;          // Clear interrupt in VIC
}

/*************************************************************************
 * Function Name: fiq_handler
 * Parameters: void
 * Return: void
 *
 * Description: FIQ subroutine
* Note: This is ARM mode code - full 32 bit code	
 *************************************************************************/
__fiq __arm void fiq_handler (void)
{
  while(1);
}

unsigned char SlaveRcv = 0xAA;
unsigned char SlaveSnd; 

void I2C0_Isr(void)
{
  unsigned char st;
  st = I2C0STAT; 
  I2C0CONCLR = 0x2C; 
  switch(st) {
      case 0x60: 
      case 0x68:
              I2C0CONSET = 0x04; 
              break ;
      case 0x80: 
              SlaveRcv = I2C0DAT;
              IO1CLR = 0x00FF0000;
              IO1SET = SlaveRcv << 16;
              break ;
      case 0x88: 
      case 0xA0: 
      case 0xC0: 
      case 0xC8: 
              I2C0CONSET = 0x04;
              break ; 
      case 0xA8: 
      case 0xB8:
              I2C0DAT = SlaveSnd;
              break ; 
      default: 
              break ;
    } 
    VICVectAddr = 0;
}

void main()
{
  PINSEL1 |= 0x01000000; 
  IO1DIR = 0x00FF0000;
  PINSEL0 |= 0x50;
  I2C0ADR = 0x20;
  I2C0CONSET = 0X44;
  
  VICVectAddr0 = (unsigned int)I2C0_Isr;
  VICVectCntl0 = 0x29;
  VICIntEnable |= 0x200;
}