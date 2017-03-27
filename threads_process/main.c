/*
============================================================================
  Author      : Elad Geva
 Version     :
 Copyright   : Your copyright notice
 Description : HOME_EX1
 ============================================================================
 */

#include "fpga.h"
#include "Globals.h"

//functions declaration
void init();
void print_msg(message*);
void set_msg(message*,const char buffer[]);
void send_message_to_mq(const char buffer[]);
void* input_func(void*);
void* fpga_func(void*);
void* display_func(void*);
void* logger_func(void*);
void close_resorces(int);

//main
int main(void) {

	    init();
     
        pthread_create(&thread_input, NULL, input_func, NULL);
        pthread_create(&thread_display, NULL, display_func, NULL);
        pthread_create(&thread_fpga, NULL, fpga_func, NULL);
        pthread_create(&thread_logger, NULL, logger_func, NULL);

        pthread_join(thread_input,NULL);
        pthread_join(thread_display,NULL);
        pthread_join(thread_fpga,NULL);
        pthread_join(thread_logger,NULL);
          
       exit(EXIT_SUCCESS);
}
//end of main
void init()
{
	// init msg queue
	    stack_att.mq_maxmsg = MQ_NUM_OF_MASSAGE;
	    stack_att.mq_flags = 0;
	    stack_att.mq_msgsize = MQ_MESSAGE_SIZE;
	    myqueue = mq_open("/myqueue", O_CREAT|O_RDWR, 0666, &stack_att);
	// init logger    
	    fdLog = open("./logger", O_CREAT | O_WRONLY |O_TRUNC, 0666); // logger
	    send_message_to_mq("Conncet to LOG....\n");
	// init fpga    
        connectFpga();
        send_message_to_mq("Conncet to FPGA....\n");
    // init semaphore
        if (sem_init(&sem_input_fpga, 0 ,0) < 0)
        	error_handle("Enable to init a semaphore");
        if (sem_init(&sem_fpga_input, 0 ,0) < 0)
            error_handle("Enable to init a semaphore");
        if (sem_init(&sem_display_input, 0 ,0) < 0)
            error_handle("Enable to init a semaphore");
        if (sem_init(&sem_input_display, 0 ,0) < 0)
            error_handle("Enable to init a semaphore");
        if (sem_init(&sem_fpga_display, 0 ,0) < 0)
            error_handle("Enable to init a semaphore");
        send_message_to_mq("intialize semaphores....\n");
   //  init signal handler
        sigemptyset(&mask);
        new.sa_handler = close_resorces;
        new.sa_mask = mask;
        new.sa_flags = 0;
        sigaction(SIGINT, &new, NULL);
}

void print_msg(message* sent_msg)
{
        write(1,sent_msg->msg,strlen(sent_msg->msg));
}

void set_msg(message* sent_msg, const char buffer[])
{
        strcpy(sent_msg->msg, buffer);
}

void send_message_to_mq(const char buffer[])
{
	if (mq_send(myqueue,buffer,strlen(buffer),1) < 0)
	   error_handle("fail to send massage to mq");	
}

void* input_func(void* arg)
{ 
	while(1)
	{
		//menu
		do 
		{
			//display the whole menu
			set_msg(&display_input_msg,menu_msg1);
			sem_post(&sem_display_input);
			sem_wait(&sem_input_display);
		
			set_msg(&display_input_msg,menu_msg2);
			sem_post(&sem_display_input);
			sem_wait(&sem_input_display);
						
			set_msg(&display_input_msg,menu_msg3);
			sem_post(&sem_display_input);
			sem_wait(&sem_input_display);						
			
			//input for option
			send_message_to_mq("user pressed...");
			scanf("%s",display_input_msg.msg);
			strcat(display_input_msg.msg,"\n");
			send_message_to_mq(display_input_msg.msg);
			
			//check input
			if((option = atoi(display_input_msg.msg)) == 0)
			{
				option = 4;
				set_msg(&display_input_msg,"user didn't enter a number....default option - disable!\n");
				sem_post(&sem_display_input);
				sem_wait(&sem_input_display);
				
				
			}
			else
				if(option < 0 || option > 6)
				{
					set_msg(&display_input_msg,input_error_msg);
					sem_post(&sem_display_input);
					sem_wait(&sem_input_display);
				}
		
		
		} while(option < 0 || option > 6);
		
		//in case of set start value or set end value 
		//input for value
		
		option--;
		
		if(fpga_opt[option] == SET_START || fpga_opt[option] == SET_STOP)
		{
			do
			{
				set_msg(&display_input_msg,enter_value_msg);
				sem_post(&sem_display_input);
				sem_wait(&sem_input_display);
				//input for value
				send_message_to_mq("user pressed...");
				scanf("%s",display_input_msg.msg);
				strcat(display_input_msg.msg,"\n");
				send_message_to_mq(display_input_msg.msg);
				//check input
				if((value = atoi(display_input_msg.msg)) == 0 )
				{
					if(fpga_opt[option] == SET_START)
						value = 0;
					else
						value = 20;
					
					set_msg(&display_input_msg,"user didn't enter a number - default value!\n");
					sem_post(&sem_display_input);
					sem_wait(&sem_input_display);
					
					
				}
				else
					if(value < MIN || value > MAX)
					{
						set_msg(&display_input_msg,input_error_msg);
						sem_post(&sem_display_input);
						sem_wait(&sem_input_display);
					
					}
				
			}
			while(value < MIN || value > MAX);
		}
		
		if (fpga_opt[option] == EXIT) 
			close_resorces(0);
		
		sem_post(&sem_fpga_input);
		sem_wait(&sem_input_fpga);
		
		if (fpga_opt[option] == GET_COUNTER)
		{
			sprintf(display_input_msg.msg,"counter = %d\n",value);
			sem_post(&sem_display_input);
			sem_wait(&sem_input_display);
			
		}
	}
}
void* display_func(void* arg)
{
	while(1)
	{
		sem_wait(&sem_display_input);
		send_message_to_mq(display_input_msg.msg);
		print_msg(&display_input_msg);
		sem_post(&sem_input_display);
	}
}

void* fpga_func(void* arg)
{
  while(1)
  {
	  sem_wait(&sem_fpga_input);
	  fpga_options[option](&value);
	  sem_post(&sem_input_fpga);
  }
}

void* logger_func(void* arg)
{
	while(1)
	{
		
		if((n = mq_receive(myqueue,mq_buff,MQ_MESSAGE_SIZE,NULL)) < 0)
			error_handle("fail to receive massage to mq");
		if(write(fdLog, mq_buff, n) < 0)
			error_handle("fail to write to log");
		
		
	}
}

void close_resorces(int sig)
{
	//puts("closing resorces...");
	send_message_to_mq("closing the system...\n\n");
	//canceling threads
	pthread_cancel(thread_input);
	pthread_cancel(thread_display);
	pthread_cancel(thread_fpga);
	pthread_cancel(thread_logger);
	//close mq
	if(mq_unlink("/myqueue") < 0)
		error_handle("fail to unlink mq");
	if( mq_close(myqueue) < 0)
			error_handle("fail to close mq");
	//close Logger
	if(close(fdLog) < 0)
		error_handle("fail to close fd");
	//close semaphres
	if(sem_destroy(&sem_input_fpga) < 0)
		error_handle("fail to destroy semaphore");
	if(sem_destroy(&sem_fpga_input) < 0)
		error_handle("fail to destroy semaphore");
	if(sem_destroy(&sem_input_display) < 0)
		error_handle("fail to destroy semaphore");
	if(sem_destroy(& sem_display_input) < 0)
		error_handle("fail to destroy semaphore");
	if(sem_destroy(&sem_fpga_display) < 0)
    	error_handle("fail to destroy semaphore");
	exit(EXIT_SUCCESS);
}







