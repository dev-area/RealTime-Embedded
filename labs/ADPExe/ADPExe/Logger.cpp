#include<iostream>
#include "UART.h"
#include "logger.h"

using namespace std;


void Logger::WriteLog(char *msg)
{
	cout << "log write...\n";
}
void Logger::WriteLogIf(char *msg,int cond)
{
	cout << "log write if...\n";
}
void Logger::DumpDataAndReport(UART *dev)
{
	char buf[255];
	dev->GetName(buf,255);
	cout << "Dump start for " << buf << "\n";
	int s=dev->GetStatus();
	cout << "Status=" << s << endl;
	if(dev->IsActive()==1)
		cout << "online\n";
	else
		cout << "offline\n";
	if(dev->IsInterruptPending() == 1)
		cout << "Interrupt is pending...\n";
	else
		cout << "No interrrupts\n";

}
