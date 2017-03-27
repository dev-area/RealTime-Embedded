/************************************************************/
/* PROJECT NAME: 2- Task                                    */
/* Project:      LPC2100 Training course                    */
/* Engineer:     T Martin        tmartin@hitex.co.uk        */
/* Filename:     main.c                                     */
/* Language:     C                      	                */
/* Compiler:     Keil ARM	V1.3		                    */
/* Assembler:    				                            */
/* O/S:			ARTX                                        */
/************************************************************/
/* COPYRIGHT: Hitex UK Ltd 		2005						*/
/* LICENSE:   THIS VERSION CREATED FOR FREE DISTRIBUTION	*/
/************************************************************/
/* Function:                                                */
/*                                                          */
/* Example 									           		*/
/*															*/
/* Demonstrates the task managment functions within RTL RTOS*/
/*															*/	
/* Oscillator frequency 12.000 Mhz							*/
/* Target board Keil MCB21000								*/
/************************************************************/

#include <RTL.h>										 // Include the ARTX header file
#include <LPC21xx.H> 

void create_all(void);

OS_TID tsk1,tsk2;										// Define the task ID variables

void set_leds_on(int num)
{
	if(num == 1)
		 IOSET1	=	0x000F0000;	
	else
		IOSET1	=	0x00F00000;	
}

void set_leds_off(int num)
{
	if(num == 1)
		IOCLR1	=	0x000F0000;	
	else
		IOCLR1	=	0x00F00000;	
}

int main (void)
{
	IODIR1 = 0x00FF0000; 									// Set all ports to output

	os_sys_init (create_all); 									// Start the RTX and call the first task

	return 0;
}


void create_all (void)									  	
{
// TODO: create here 2 tasks 
while(1);
}

// TODO: define the tasks function here 
// blink leds on and off with delay
// use the function os_dly_wait for different delay


