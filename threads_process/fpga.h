

#ifndef FPGA_H_
#define FPGA_H_

#include "headers.h"


#define error_handle(msg) do{send_message_to_mq(msg); exit(EXIT_FAILURE);}while(0);



typedef struct
{
        char REC[256];
        int DATA;
        int MATCH;
        int START;
        int END;
        int ENABLE;
        int DISABLE;
        int STATUS;


}FPGA;

enum fpga_options  {SET_START, SET_STOP, ENABLE_COUNTER, DISABLE_COUNTER, GET_COUNTER, EXIT};

void connectFpga(void);
void enableCounter(int*);
void disableCounter(int*);
void setStart(int*);
void setStop(int*);
void getCounter(int*);


#endif /*FPGA_H_*/






