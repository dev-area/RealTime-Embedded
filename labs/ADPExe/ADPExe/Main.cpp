#include<iostream>
#include "UART.h"
#include "logger.h"

using namespace std;


void main()
{
	UART u1("com1");
	Logger log1;
	u1.UpdateStatus(&log1);
}