#include <stdio.h>
#include "resource.h"
#include "task.h"

#ifndef CONFIG_H
#define CONFIG_H

#endif

#define STACKSIZE 1024*32

ucontext_t main_ctx;// ucontext main
task_queue_type taskQ[TASKS_COUNT];
char task_stack[TASKS_COUNT][STACKSIZE];
unsigned char resource_handle[RESOURCES_COUNT];
int queue_size = 0;

int re_op_size = 0;
