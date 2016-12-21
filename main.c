#include <stdio.h>
#include <stdlib.h>
#include "num_list.h"
#include "stack.h"
#include "manager.h"

int main()
{
    list *num1 = NULL;
    list *num2 = NULL;
    char c = '\0';
    stack *main_stack = stack_make();
    
    while (1)
    {
        c = fgetc(stdin);
        switch(c)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                num1 = get_list(c);
                push(main_stack, num1);
                break;
            case '=':
                if (pick(main_stack))
                {
                    list_print(pick(main_stack));
                }
                else 
                {
                    printf("there is no numbers in stack\n");
                }
                break;
            case ' ':
            case '\n':
                break;
            default:
                if (c == '-')
                {
                    c = fgetc(stdin);
                    if (c == '\n' || c == ' ')
                    {
                        c = '-';
                    }
                    else
                    {
                        num1 = get_list(c);
                        num1->sign = 1;
                        push(main_stack, num1);
                        continue;
                    }
                }
                num2 = pop(main_stack);
                num1 = pop(main_stack);
                if (!num1 || !num2)
                {
                    if (num2)
                    {
                        push(main_stack, num2);
                    }
                    fprintf(stderr, "can not do operation due to empty stack\n");
                    continue;
                }
                operator_switch(c, num1, num2, main_stack);
                break;
        }
    }
    return 0;
}

