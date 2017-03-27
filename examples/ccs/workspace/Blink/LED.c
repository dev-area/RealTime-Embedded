/******************************************************************************/
/************* Sample LED blinking application program ************************/
/************* for use on Hawkboard *******************************************/
/************* AUthor - Lakshminarayan.V **************************************/
/************* COmpany : Innovate Software Solutions Pvt Ltd ******************/
/************* website : www.innovatesolutions.net ****************************/
/******************************************************************************/


#define DELAY   0xFFFFF		/* delay for time interval between led blink */
volatile unsigned int *LED_DIR = (volatile unsigned int *) 0x01E26088;		/* GPIO Direction register Address */
volatile unsigned int *LED_OUT_DATA = (volatile unsigned int *) 0x01E2608C;	/* GPIO Output Data register Address */

void configure_gpio(void);
void blink1(void);
void blink2(void);
void delay(void);



int main()
{
	volatile int *p=(volatile int *)0xc1011ff8;
	int val;	
	configure_gpio();

	while(1)
	{
		blink1();	/* LED BLINK Pattern #1 - 25 times */
		val=*p;
		blink2();	/* LED BLINK Pattern #2 - 25 times */
	}

}

void configure_gpio(void)
{
	volatile unsigned int *GP6 = (volatile unsigned int *) 0x01C14154;		/* GPIO6 pinmux register */
	*GP6 = 0x8800;					/* Pin Mux for GPIO6(12) & GPIO6(13) */
	*LED_DIR = (unsigned int) (*LED_DIR & (0xFFFFCFFF )); 	/* Set GPIO Direction to output */
}	 

void blink1(void)
{
	int i;
	*LED_OUT_DATA = (unsigned int) (*LED_OUT_DATA & ~(0x3 << 12));	/* switch OFF both LEDs */
	for(i=25;i>0;i--)
	{
		*LED_OUT_DATA = (unsigned int) (*LED_OUT_DATA |(0x1 << 12)); /* Switch one LED ON */
		delay();
		*LED_OUT_DATA = (unsigned int) (*LED_OUT_DATA & ~(0x3 << 12));	/* switch OFF both LEDs */
		*LED_OUT_DATA = (unsigned int) (*LED_OUT_DATA | (0x2 << 12)); /* Switch Other LED ON */
		delay();
		*LED_OUT_DATA = (unsigned int) (*LED_OUT_DATA & ~(0x3 << 12));	/* switch OFF both LEDs */
	}	
}

void blink2(void)
{
	int i;
	*LED_OUT_DATA =  (unsigned int)(*LED_OUT_DATA & ~(0x3 << 12));	/* switch OFF both LEDs */
	for(i=25;i>0;i--)
	{
		*LED_OUT_DATA = (unsigned int) (*LED_OUT_DATA & ~(0x3 << 12));	/* Switch OFF both LEDs */
		delay();
		*LED_OUT_DATA = (unsigned int) (*LED_OUT_DATA | (0x3 << 12));	/* Switch ON Both LEDs */
		delay();
	}	
}

void delay(void)
{
	unsigned int i;
	for(i=DELAY;i>0;i--)
	{
	}
}

