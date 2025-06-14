#include "task.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

struct task tsk[256];
bool is_task_uptodate = true;

void reorder_task_list() {
  uint16_t count = 1;
  for (uint16_t index = 0; index < MAX_TASK; index++) { 
    if (tsk[index].is_occupied) {
      tsk[index].task_id = count;
      count++;
    }
  }
}

void init() {
  for (uint16_t index = 0; index < MAX_TASK; index++) {
    tsk[index].is_occupied = false;
    tsk[index].is_done = false;
  }
}

void add_task() {
  char local_task_name[512];

  printf("Enter task name :");
  fgets(local_task_name, 255, stdin);

  int len = strlen(local_task_name);
  local_task_name[len - 1] = '\0'; // replace newline with null character

  for (uint16_t index = 0; index < MAX_TASK; index++) {
    if (!tsk[index].is_occupied) {
      strcpy(tsk[index].task_name, local_task_name);
      tsk[index].is_occupied = true;
      break;
    }
  }

  reorder_task_list();
  is_task_uptodate = false;
}

void list_task() {
  printf("\n ***********TASKS*************\n\n");
  for (uint16_t index = 0; index < MAX_TASK; index++) {

    if (tsk[index].is_occupied) {
      char pending[] = "Pending";
      char done[] = "Completed";
      printf("%d. %s Status : %s index = %d\n", tsk[index].task_id,
             tsk[index].task_name, (tsk[index].is_done) ? done : pending,
             index);
    }
  }
  printf("\n*****************************\n");
}

void done(uint16_t *id) {
  uint16_t value = *id;
  for (uint16_t index = 0; index < MAX_TASK; index++) {

    if (tsk[index].task_id == value) {
      if (tsk[index].is_done) {
        printf("Task is already marked as done.\n");
      } else {
        tsk[index].is_done = true;
      }
      break;
    }
  }
}

void delete_task(uint16_t *id) {
    uint16_t index = 0;
  for (; index < MAX_TASK; index++) {
    if (tsk[index].task_id == *id) {
      tsk[index].is_occupied = false;
      tsk[index].is_done = false;
      break;
    }
  }
  reorder_task_list();
  is_task_uptodate = false;
}

void save_task() {
  if (is_task_uptodate) {
    printf("Task List file is already up-to-date\n");
    return;
  } 

  FILE *fd;
  fd = fopen("task.txt", "w");
  if (fd == NULL) {
    printf("Failed to Open task list file('task.txt')");
  } else {
    for (uint16_t i = 0; i < MAX_TASK; i++) {
      char append_string[MAX_MEM_POOL];
      if ((snprintf(append_string, sizeof(append_string), "%d. %s : ", tsk[i].task_id,
                   tsk[i].task_name)) > 0 &&
          strlen(tsk[i].task_name) > 0) {
        fputs(append_string, fd);
        fputs("\n", fd);
      }
    }
    printf("Successfully saved task list in file.\n");
  }
  fclose(fd);
}

void load_task()
{
  FILE *fd;
  fd = fopen("task.txt", "r");
  if (fd != NULL) {
    if (fgetc(fd) != EOF) {
      rewind(fd);
      char buf[MAX_MEM_POOL];
      char ch = '.';
      int16_t index = 0;
      while (fgets(buf, sizeof(buf), fd) != NULL) {
        const char *res = strchr(buf, ch);
        if (res == NULL)
          return;
        int pos = res - buf;
        const char* new = buf+pos+2;
        strcpy(tsk[index].task_name, new);
        tsk[index].is_occupied = true;
        int len = strlen(tsk[index].task_name);
        tsk[index].task_name[len - 1] = '\0';
        index++;
      }
      reorder_task_list();
    }
  }
  else {
    printf("Cannot find the task.txt\n");
  }
  fclose(fd);
}
