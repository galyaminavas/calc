#include <stdio.h>
#include <stdlib.h>
#include "num_list.h"
#include "stack.h"
#include "manager.h"

/*void swap(list *l1, list *l2)
{
    list *buff;
    buff = *l1;
    *l1 = *l2;
    *l2 = buff;
}*/

void operator_switch (char oper, list *l1, list *l2, stack *s)
{
    int sumsigns = l1->sign * 2 + l2->sign;
    switch(oper)
    {
        case '+':
        {
            switch(sumsigns)
            {
                case 1:
                case 2:
                    if (compare_lists(l1, l2) >= 0)
                    {
                        push(s, list_subtraction(l1, l2));
                    }
                    else
                    {
                        push(s, list_subtraction(l2, l1));
                    }
                    break;
                case 0:
                case 3:
                    if (compare_lists(l1, l2) >= 0)
                    {
                        push(s, list_addition(l1, l2));
                    }
                    else
                    {
                        push(s, list_addition(l2, l1));
                    }
                    break;
                default:
                    break;
            }
            break;
        }
        case '-':
        {
            switch(sumsigns)
            {
                case 0:
                    if (compare_lists(l1, l2) >= 0)
                    {
                        push(s, list_subtraction(l1, l2));
                    }
                    else
                    {
                        l2->sign = 1;
                        push(s, list_subtraction(l2, l1));
                    }
                    break;
                case 1:
                    l2->sign = 0;
                    if (compare_lists(l1, l2) >= 0)
                    {
                        push(s, list_addition(l1, l2));
                    }
                    else
                    {
                        push(s, list_addition(l2, l1));
                    }
                    break;
                case 2:
                    if (compare_lists(l1, l2) >= 0)
                    {
                        push(s, list_addition(l1, l2));
                    }
                    else
                    {
                        l2->sign = 1;
                        push(s, list_addition(l2, l1));
                    }
                    break;
                case 3:
                    l2->sign = 0;
                    if (compare_lists(l1, l2) >= 0)
                    {
                        push(s, list_subtraction(l1, l2));
                    }
                    else
                    {
                        push(s, list_subtraction(l2, l1));
                    }
                    break;
                default:
                    break;
            }
            break;
        }
        case '*':
        {
            switch(sumsigns)
            {
                case 0:
                case 3:
                {
                    if (compare_lists(l1, l2) >= 0)
                    {
                        l1->sign = 0;
                        push(s, list_mult(l1, l2));
                    }
                    else
                    {
                        l2->sign = 0;
                        push(s, list_mult(l2, l1));
                    }
                    break;
                }
                case 1:
                case 2:
                {
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list *result = list_mult(l1, l2);
                        result->sign = 1;
                        push(s, result);
                    }
                    else
                    {
                        list *result = list_mult(l1, l2);
                        result->sign = 1;
                        push(s, result);
                    }
                    break;
                }
            }
        }
        case '/':
        {
            if (list_len(l2) == 1 && l2->first->value == 0)
            {
                printf("you should not divide by zero\n");
                break;
            }
            switch(sumsigns)
            {
                case 0:
                case 3:
                {
                    push(s, list_div(l1, l2));
                    break;
                }
                case 1:
                case 2:
                {
                    list *l0 = list_make();
                    l0 = list_div(l1, l2);
                    if (compare_lists(l1, l2) >= 0)
                    {
                        l0->sign = 1;
                        push(s, l0);
                    }
                    else
                    {
                        push(s, l0);
                    }
                    break;
                }
            }
        }
        default:
        {
            printf("incorrect input");
            break;
        }
    }
}