#ifndef GLOBALS_H_
#define GLOBALS_H_

#define MESSAGE_SIZE 255
#define MQ_MESSAGE_SIZE 255 // (bytes)
#define MQ_NUM_OF_MASSAGE 20 
#define MIN 0
#define MAX 999

typedef char buff[MESSAGE_SIZE];
typedef struct
{
	buff msg;
}message;

message display_input_msg = {""};
//messages from output to input
const char menu_msg1[] = "1. set start value\n2 .set stop value\n";
const char menu_msg2[] = "3. enable counter\n4. disable counter\n";
const char menu_msg3[] = "5. print counter value\n6. exit\n";
const char enter_value_msg[] = "please enter a value 0-999\n";
const char input_error_msg[] = "input error\n";
//fpga vals
void(*fpga_options[])(int*) = {setStart, setStop, enableCounter, disableCounter, getCounter};
enum fpga_options fpga_opt[] = {SET_START, SET_STOP, ENABLE_COUNTER, DISABLE_COUNTER, GET_COUNTER, EXIT};

int fdLog ; //log file descriptor

//mq vars
mqd_t myqueue;
struct mq_attr stack_att = {0};
buff mq_buff = "";
//signal handler vars
sigset_t mask;
struct sigaction new;
//global vars
int option;
int value;
int n;
//semaphores
sem_t sem_input_fpga;
sem_t sem_fpga_input;
sem_t sem_input_display;
sem_t sem_display_input;
sem_t sem_fpga_display;
//threads
pthread_t thread_input;
pthread_t thread_display;
pthread_t thread_fpga;
pthread_t thread_logger;

#endif /*GLOBALS_H_*/
