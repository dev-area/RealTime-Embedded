/******************************************************************************/
/* HELLO.C: Hello World Example                                               */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2006 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <stdio.h>                /* prototype declarations for I/O functions */
#include <LPC21xx.H>              /* LPC21xx definitions                      */

void wait (void)  {                        /* wait function */
  int  d;

  for (d = 0; d < 1000000; d++);           /* only to delay for LED flashes */
}
void init_uart()
{
  /* initialize the serial interface   */
  PINSEL0 = 0x00050000;           /* Enable RxD1 and TxD1                     */
  U1LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit            */
  U1DLL = 97;                     /* 9600 Baud Rate @ 15MHz VPB Clock         */
  U1LCR = 0x03;                   /* DLAB = 0                                 */

}
void init_gpio()
{
                       /* P0.16..19 defined as Outputs */
}

unsigned int count_bits(unsigned int val)
{
	int res;
	// count the high bits (1) 
	return res;
}
void write_gpio(unsigned int res)
{
	//send result to bits 16:19
}
/****************/
/* main program */
/****************/
int main (void)  {                

	//init the hardware (UART , GPIO0)
  while (1) {                          
	// read from gpio
	// count the high bits
	// update result in gpio
	// send message on uart

  }                                    

}
