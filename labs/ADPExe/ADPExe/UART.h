#ifndef __UART
#define __UART
#include "logger.h"

class UART
{
	int baseaddr;
	char name[255];
public:
	UART(char *n){strcpy(name,n);}
	void SendData(char *msg);
	void GetData(char *buf,int size);
	void UpdateStatus(Logger *log);
	int GetStatus();
	int IsInterruptPending();
	int IsActive();
	int GetName(char *buf,int size);
};


#endif