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

void task1 (void) ;								 // Tsk function prototypes
void task2 (void) ;
void create_all(void);
void one_task(void *p);

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

void main (void)
{
IODIR1 = 0x00FF0000; 									// Set all ports to output

os_sys_init (create_all); 									// Start the RTX and call the first task
}


void create_all (void)									  	
{

tsk1 = os_tsk_create(task1,0x10);
tsk2 = os_tsk_create(task2,0x10);				   				
//tsk1 = os_tsk_create_ex(one_task,0x10,(void *)1);
//tsk2 = os_tsk_create_ex(one_task,0x10,(void *)2);				   				

while(1);
}

void task1 (void)									   				
{

	while(1)
	{
		set_leds_on(1);
		os_dly_wait(12);												  	
		set_leds_off(1);
		os_dly_wait(12);	
	}
}
void task2 (void)									   				
{

	while(1)
	{
		set_leds_on(2);
		os_dly_wait(20);												  	
		set_leds_off(2);
		os_dly_wait(20);	
	}
}

void one_task(void *arg)
{
	int leds = (int)arg;
	while(1)
	{
		set_leds_on(leds);
		os_dly_wait(20);												  	
		set_leds_off(leds);
		os_dly_wait(20);	
	}


}
