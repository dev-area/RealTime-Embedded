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
	task_handler_t new_tsk=NULL;
	new_tsk = (task_handler_t) calloc (1,sizeof(task_t));
	if (new_tsk == NULL)
	{
		fprintf (stderr, "Error allocating memory\n");
		return NULL;
	}
	new_tsk->state = RUNNING;
	new_tsk->priority = 10;
	new_tsk->num = task_numbers;
	task_numbers++;
	return new_tsk;
}


unsigned int task_get_priority(task_handler_t tsk)
{
	return tsk->priority;
}

void task_set_priority(task_handler_t tsk,int p_priority)
{
	tsk->priority = p_priority;
}

void task_suspend (task_handler_t tsk)
{
	tsk->state = SUSPENDED;
}
void task_resume (task_handler_t tsk)
{
	tsk->state = RUNNING;
}
void task_destroy (task_handler_t tsk)
{
	if(tsk)
		free(tsk);
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

