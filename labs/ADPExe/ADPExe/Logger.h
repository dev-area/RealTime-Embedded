#ifndef __LOGGER
#define __LOGGER
#include "UART.h"
class UART;

class Logger
{
	char *filename;
public:
	void WriteLog(char *msg);
	void WriteLogIf(char *msg,int cond);
	void DumpDataAndReport(UART *dev);
};


#endif