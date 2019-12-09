#include "task.h"
#ifndef SCHEDULING_SIMULATOR_H
#define SCHEDULING_SIMULATOR_H
#endif


status_type activate_task(task_type id)
{
    status_type result = STATUS_OK;
    if(taskQ[id].state == 2)
    {
        taskQ[id].state = 1;
        taskQ[running_task_id].state = 1;
        queue_size++;
        if(swapcontext(&(taskQ[running_task_id].task_ucontext),&main_ctx) == -1)
        {
            perror("swaperror");
        }
        result = STATUS_OK;
    }
    else
    {
        result = STATUS_ERROR;
    }

    return result;
}

status_type terminate_task(void)
{
    status_type result;
    if(taskQ[running_task_id].occupied_res == 0)
    {

        result = STATUS_OK;
        taskQ[running_task_id].state = 2;
        taskQ[running_task_id].act_times -= 1;
        int i = 0;
        for(i = 0; i < TASKS_COUNT; i++)
        {
            if(taskQ[i].state == 1 && taskQ[i].turn > taskQ[running_task_id].turn)
            {
                taskQ[i].turn -= 1;
            }
        }
        taskQ[running_task_id].turn = TASKS_COUNT+1;
        turn--;

    }
    else
    {
        result = STATUS_ERROR;
    }




    return result;
}
