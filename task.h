#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include "typedefine.h"
#include "config.h"

status_type activate_task(task_type id);
status_type terminate_task(void);

#define STACKSIZE 1024*32
extern ucontext_t main_ctx;
extern task_queue_type taskQ[TASKS_COUNT];
extern char task_stack[TASKS_COUNT][STACKSIZE];
extern unsigned char resource_handle[RESOURCES_COUNT];
extern int queue_size;
extern int running_task_id;
extern int turn;


#endif /* TASK_H */
