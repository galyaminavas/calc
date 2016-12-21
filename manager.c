#include <stdio.h>
#include <stdlib.h>
#include "num_list.h"
#include "stack.h"
#include "manager.h"

void operator_switch (char oper, list *l1, list *l2, stack *s)
{
    int sumsigns = l1->sign * 2 + l2->sign;
    switch(oper)
    {
        case '+':
            switch(sumsigns)
            {
                case 1:
                case 2:
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list *result = list_make();
                        result = list_subtraction(l1, l2);
                        push(s, result);
                    }
                    else
                    {
                        list *result = list_make();
                        result = list_subtraction(l2, l1);
                        push(s, result);
                    }
                    break;
                case 0:
                case 3:
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list *result = list_make();
                        result = list_addition(l1, l2);
                        push(s, result);
                    }
                    else
                    {
                        list *result = list_make();
                        result = list_addition(l2, l1);
                        push(s, result);
                    }
                    break;
                default:
                    break;
            }
            break;
        case '-':
            switch(sumsigns)
            {
                case 0:
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list *result = list_make();
                        result = list_subtraction(l1, l2);
                        push(s, result);
                    }
                    else
                    {
                        l2->sign = 1;
                        list *result = list_make();
                        result = list_subtraction(l2, l1);
                        push(s, result);
                    }
                    break;
                case 1:
                    l2->sign = 0;
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list *result = list_make();
                        result = list_addition(l1, l2);
                        push(s, result);
                    }
                    else
                    {
                        list *result = list_make();
                        result = list_addition(l2, l1);
                        push(s, result);
                    }
                    break;
                case 2:
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list *result = list_make();
                        result = list_addition(l1, l2);
                        push(s, result);
                    }
                    else
                    {
                        l2->sign = 1;
                        list *result = list_make();
                        result = list_addition(l2, l1);
                        push(s, result);
                    }
                    break;
                case 3:
                    l2->sign = 0;
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list *result = list_make();
                        result = list_subtraction(l1, l2);
                        push(s, result);
                    }
                    else
                    {
                        list *result = list_make();
                        result = list_subtraction(l2, l1);
                        push(s, result);
                    }
                    break;
                default:
                    break;
            }
            break;
        case '*':
            switch(sumsigns)
            {
                case 0:
                case 3:
                {
                    if (compare_lists(l1, l2) >= 0)
                    {
                        l1->sign = 0;
                        list *result = list_make();
                        result = list_mult(l1, l2);
                        push(s, result);
                    }
                    else
                    {
                        l2->sign = 0;
                        list *result = list_make();
                        result = list_mult(l2, l1);
                        push(s, result);
                    }
                    break;
                }
                case 1:
                case 2:
                {
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list *result = list_make();
                        result = list_mult(l1, l2);
                        result->sign = 1;
                        push(s, result);
                    }
                    else
                    {
                        list *result = list_make();
                        result = list_mult(l2, l1);
                        result->sign = 1;
                        push(s, result);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        case '/':
            if (list_len(l2) == 1 && l2->first->value == 0)
            {
                printf("you should not divide by zero\n");
                push(s, l1);
                push(s, l2);
                break;
            }
            switch(sumsigns)
            {
                case 0:
                case 3:
                {
                    list *result = list_make();
                    result = list_div(l1, l2);
                    push(s, result);
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
                default:
                    break;
            }
            break;
        default:
            break;
    }
}