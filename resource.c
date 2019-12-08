#include <stdio.h>
#include "resource.h"
#ifndef SCHEDULING_SIMULATOR_H
#define SCHEDULING_SIMULATOR_H
#endif

status_type get_resource(resource_type id)
{
    status_type result;
    if(resource_handle[id] == 0)
    {
        resource_handle[id] = running_task_id;
        taskQ[running_task_id].occupied_res += 1;
        taskQ[running_task_id].now_priority = resources_priority[id];

        taskQ[running_task_id].state = 1;

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

status_type release_resource(resource_type id)
{
    status_type result;
    if(resource_handle[id] == running_task_id)
    {
        resource_handle[id] = 0;
        taskQ[running_task_id].occupied_res -= 1;
        taskQ[running_task_id].now_priority = task_const[running_task_id].static_priority;

        taskQ[running_task_id].state = 1;

        if(swapcontext(&(taskQ[running_task_id].task_ucontext),&main_ctx) == -1)
        {
            perror("swaperror");
        }
        result =  STATUS_OK;
    }
    else
    {
        result = STATUS_ERROR;
    }

    return result;
}
