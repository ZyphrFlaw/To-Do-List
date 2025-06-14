#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_TASK 256
#define MAX_MEM_POOL 512

typedef struct task
{
    uint8_t task_id;
    char task_name[512];
    bool is_done;
    bool is_occupied;
}task;

void init();
void add_task();
void list_task();
void save_task();
void done(uint16_t *id);
void delete_task(uint16_t* id);
void load_task();
