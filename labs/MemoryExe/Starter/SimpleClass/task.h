struct task;
typedef struct task* task_handler_t;

unsigned int		task_get_priority(task_handler_t tsk);
void				task_suspend (task_handler_t tsk);
void				task_resume (task_handler_t tsk);
void				task_set_priority(task_handler_t tsk,int priority);
task_handler_t		task_construct (void);
void				task_destroy (task_handler_t tsk);
void				task_print_status(task_handler_t tsk);
