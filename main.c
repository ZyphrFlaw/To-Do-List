
#include "menu.h"
#include "task.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern struct task tsk[256];
extern uint32_t tsk_cnt;


int main()
{
    int id = 1;
    init();
    while( true )
    {
        Menu();
        scanf("%d", &id);

        int c;

        // Using below method to remove '\n' from input stream
        while ((c = getchar()) != EOF && c != '\n') ; // Avoid using scanf() and fgets() together as newline ('\n') doesn't get flushed and remains in the input stream.
        
        switch (id)
        {
            case 1: add_task();
                break;
            case 2: list_task();
                break;
            case 3: 
            {
                uint16_t val = 0;
                printf("Enter task ID to mark it as completed. : ");
                scanf("%"SCNu16, &val);
                done(&val);
            }break;
        
            case 4:
            {
                uint16_t id = 0;
                printf("Enter the task ID to delete it : ");
                scanf("%"SCNu16, &id);
                delete_task(&id);
            }break;

            case 7:
                return 0;
                break;
        
        default:
            break;
        }
    }
    return 0;
}