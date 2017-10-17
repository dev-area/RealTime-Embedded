#include<iostream>
#include "UART.h"
#include "logger.h"

using namespace std;

void UART::SendData(char *msg)
{
	cout << "send...\n";
}
int UART::GetName(char *buf,int size)
{
	if(size<=255)
	{
		strcpy(buf,name);
		return 0;
	}
	return -1;
}

void UART::GetData(char *buf,int size)
{
	cout << "get...\n";
}
void UART::UpdateStatus(Logger *log)
{
	cout << "start...\n";
	log->DumpDataAndReport(this);
	cout << "end...\n";
}
int UART::GetStatus()
{
	return 0x100;
}

int UART::IsInterruptPending()
{
	return 1;
}
int UART::IsActive()
{
	return 1;
}

