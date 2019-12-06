#include "task.h"
#ifndef SCHEDULING_SIMULATOR_H
#define SCHEDULING_SIMULATOR_H
#endif


status_type activate_task(task_type id)
{
    printf("in act");
    status_type result = STATUS_OK;
    if(taskQ[id].state == 2)
    {
        taskQ[id].state = 1;
        queue_size++;
        printf("in act: before swap\n");
        //taskQ[running_task_id].state = 3;
        //taskQ[running_task_id].state = 1;
        if(swapcontext(&(taskQ[running_task_id].task_ucontext),&main_ctx) == -1)
        {
            perror("swaperror");
        }
        printf("in act: after swap\n");
        result = STATUS_OK;
    }
    else
    {
        result = STATUS_ERROR;
    }

    printf("in act: before res\n");
    return result;
}

status_type terminate_task(void)
{
    status_type result = STATUS_OK;

    return result;
}
