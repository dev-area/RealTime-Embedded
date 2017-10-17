#include<stdio.h>

#include "task.h"


int main()
{
	task_handler_t ts1,ts2;
	ts1 = task_construct();
	task_set_priority(ts1,15);
	task_print_status(ts1);
	printf("======================\n");
	ts2 = task_construct();
	task_set_priority(ts2,5);
	task_suspend(ts2);
	task_print_status(ts2);

	task_destroy(ts1);
	task_destroy(ts2);
	return 0;
}