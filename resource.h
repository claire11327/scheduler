#ifndef RESOURCE_H
#define RESOURCE_H

#include "typedefine.h"
#include "config.h"

status_type get_resource(resource_type id);
status_type release_resource(resource_type id);

#define STACKSIZE 1024*32
extern ucontext_t main_ctx;
extern task_queue_type taskQ[TASKS_COUNT];
extern char task_stack[TASKS_COUNT][STACKSIZE];
extern unsigned char resource_handle[RESOURCES_COUNT];
extern int queue_size;
extern int running_task_id;

#endif /* RESOURCE_H */
