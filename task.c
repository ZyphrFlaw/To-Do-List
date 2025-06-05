#include "task.h"

uint32_t tsk_cnt = 0;
struct task tsk[256];

void init()
{
    for (uint16_t index = 0; index < MAX_TASK; index++)
    {
        tsk[index].is_occupied = false;
        tsk[index].is_done = false;
    }
}

void add_task()
{
    char local_task_name[256];

    printf("Enter task name :");
    fgets(local_task_name, 255, stdin);

    int len = strlen(local_task_name);
    local_task_name [ len - 1 ] = '\0'; // replace newline with null character
    
    uint16_t count = 1;
    for (uint16_t index = 0; index < MAX_TASK; index++)
    {
        if ( !tsk[index].is_occupied )
        {
            strcpy(tsk[index].task_name, local_task_name);
            tsk[index].task_id = count;
            tsk[index].is_occupied = true;
            break;
        }
        else
            count++;
    }
    printf("Task Add successfully!!!\n");
}

void list_task()
{
    printf("\n ***********TASKS*************\n\n");
    for (uint16_t index = 0; index < MAX_TASK; index++)
    {
        
        if ( tsk[index].is_occupied )
        {
            char pending[] = "Pending";
            char done[] = "Completed";
            printf("%d. %s. Status : %s\n", tsk[index].task_id, tsk[index].task_name,(tsk[index].is_done) ? done : pending);
        }
    }
    printf("\n*****************************\n");
}

void done(uint16_t* id)
{
    uint16_t value = *id;
    for (uint16_t index = 0; index < MAX_TASK; index++)
    {

        if (tsk[index].task_id == value)
        {
            if (tsk[index].is_done)
            {
                printf("Task is already marked as done.");
            }
            else
            {
                tsk[index].is_done = true;
            }
            break;
        }
    }
    
}

void delete_task(uint16_t* id)
{

    int16_t count = 1;
    for (int16_t index = 0; index < MAX_TASK; index++)
    {
        if (tsk[index].task_id == *id)
        {
            tsk[index].is_occupied = false;
            tsk[index].is_done = false;
            break;
        }
    }

    //reorder as per task
    for (uint16_t index = 0; index < MAX_TASK; index++)
    {
        if ( tsk[index].is_occupied )
        {
            tsk[index].task_id = count;
        }
        else
            count++;
    }

}