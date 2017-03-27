

#include "fpga.h"

 static volatile FPGA* myfpga   ; // pointer to virtual memory

void connectFpga(void)
{
	int fd; 
    if( (fd = open("/dev/mem", O_RDWR | O_SYNC ,0)) < 0)
    {
       perror("fail to open device");
       exit(EXIT_FAILURE);
    }
    if( (myfpga = mmap(0 ,0x1000 ,PROT_READ|PROT_WRITE, MAP_SHARED,fd , 0x101e9000)) <0)
    {
           perror("fail to mmap");
           exit(EXIT_FAILURE);
    }
}
void enableCounter(int* val)
{
        myfpga->ENABLE = 1;

}
void disableCounter(int* val)
{
        myfpga->DISABLE = 1;

}
void setStart(int* val)
{
        myfpga->START =  *val;
       
}
void setStop(int* val)
{
        myfpga->END =  *val;
      
}
void getCounter(int* val)
{
       *val = myfpga->DATA;
}

