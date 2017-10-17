#include "task.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {	SUSPENDED, 
				RUNNING
} task_state;

typedef struct task
{
	task_state state;
	unsigned int num;
	unsigned int priority;
	void (*func)(void);
} task_t;

static unsigned int task_numbers=0;

task_handler_t task_construct (void)
{
	// TODO: implement 
}


unsigned int task_get_priority(task_handler_t tsk)
{
	// TODO: implement 
}

void task_set_priority(task_handler_t tsk,int p_priority)
{
	// TODO: implement 
}

void task_suspend (task_handler_t tsk)
{
	// TODO: implement 
}
void task_resume (task_handler_t tsk)
{
	// TODO: implement 
}
void task_destroy (task_handler_t tsk)
{
	// TODO: implement 
}

void task_print_status(task_handler_t tsk)
{
	printf("task number:%d\n",tsk->num);
	printf("task priority:%d\n",tsk->priority);
	if(tsk->state == SUSPENDED)
		printf("task is suspended\n");
	else
		printf("task is running\n");
}

