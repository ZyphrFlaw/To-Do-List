#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_TASK 265

extern struct task
{
    uint8_t task_id;
    char task_name[256];
    bool is_done;
    bool is_occupied;
}task;

extern struct task tsk[256];

void init();
void add_task();
void list_task();
void done(uint16_t *id);
void delete_task(uint16_t* id);