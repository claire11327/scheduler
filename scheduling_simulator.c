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
int running_task_id = -1;
int turn = 0;


int init = -1;

int main()
{
    int i = 0;

    if(init == -1)
    {
        init = 0;
        for(i = 0; i< TASKS_COUNT; i++)
        {
            taskQ[i].taskData = task_const[i];
            taskQ[i].now_priority = task_const[i].static_priority;
            taskQ[i].occupied_res = 0;
            taskQ[i].state = 2;
            taskQ[i].turn = TASKS_COUNT+1;
            taskQ[i].act_times = 0;
            if(getcontext(&(taskQ[i].task_ucontext))== -1 &&
                    sizeof(taskQ[i].task_ucontext.uc_stack.ss_size) != 0)
                perror("getcontext failure: ");

            taskQ[i].task_ucontext.uc_link = &main_ctx;
            taskQ[i].task_ucontext.uc_stack.ss_sp =  task_stack[i];
            taskQ[i].task_ucontext.uc_stack.ss_size = STACKSIZE;
            taskQ[i].task_ucontext.uc_stack.ss_flags = 0;
            makecontext(&(taskQ[i].task_ucontext),task_const[i].entry, 0);
        }
    }



    for(i = 0; i < RESOURCES_COUNT; i++)
    {
        resource_handle[i] = 0;
    }
    int autolist_size = sizeof(auto_start_tasks_list);
    for(i = 0; i < autolist_size; i++)
    {
        taskQ[auto_start_tasks_list[i]].state = 1;
        taskQ[auto_start_tasks_list[i]].act_times = 1;
        queue_size++;
    }
    getcontext(&main_ctx);
    while (1)
    {
        int func = 0;
        unsigned char phigh = 0;
        for(i = 0; i < TASKS_COUNT; i++)
        {
            if(taskQ[i].state == 1)
            {
                if(taskQ[i].turn > TASKS_COUNT)
                {
                    taskQ[i].turn = turn;
                    turn++;
                }
                if(phigh < taskQ[i].now_priority ||  (phigh == taskQ[i].now_priority && taskQ[func].turn > taskQ[i].turn ))
                {
                    phigh = taskQ[i].now_priority;
                    func = i;
                }
            }
        }
        if(queue_size != 0)
        {
            if(taskQ[func].act_times < 0 )
            {
                taskQ[func].act_times += 1;
                makecontext(&(taskQ[func].task_ucontext),task_const[func].entry, 0);
            }
            if(running_task_id != func)
            {
                taskQ[func].state = 0;
                running_task_id = func;
                swapcontext(&main_ctx,&(taskQ[func].task_ucontext));

            }
            else
            {
                running_task_id = func;
                swapcontext(&main_ctx,&(taskQ[func].task_ucontext));
            }

        }
        else
            break;

    }
    return 0;
}

