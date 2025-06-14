#include "menu.h"
#include "task.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  int id = 0;
  init();
  load_task();
  while (true) {
    Menu();
    scanf("%d", &id);

    int c;

    // Using below method to remove '\n' from input stream
    while ((c = getchar()) != EOF && c != '\n')
      ; // Avoid using scanf() and fgets() together as newline ('\n') doesn't
        // get flushed and remains in the input stream.
    switch (id) {
    case 1:
      add_task();
      break;
    case 2:
      list_task();
      break;
    case 3: {
      uint16_t val = 0;
      printf("Enter task ID to mark it as completed. : ");
      scanf("%" SCNu16, &val);
      done(&val);
    } break;

    case 4: {
      uint16_t id = 0;
      printf("Enter the task ID to delete it : ");
      scanf("%" SCNu16, &id);
      delete_task(&id);
    } break;

    case 5: 
    {
      save_task();
    } break;

    case 6: {
      load_task();
    } break;

    case 7:
      return 0;
      break;

    default:
      return 0;
      break;
    }
  }
  return 0;
}
