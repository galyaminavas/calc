#include <stdio.h>
#include <stdlib.h>
#include "num_list.h"
#include "stack.h"
#include "manager.h"

void operator_switch (char oper, list *l1, list *l2)
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
                        list_subtraction(l1, l2);
                    }
                    else
                    {
                        list_subtraction(l2, l1);
                    }
                    break;
                case 0:
                case 3:
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list_addition(l1, l2);
                    }
                    else
                    {
                        list_addition(l2, l1);
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
                        list_subtraction(l1, l2);
                    }
                    else
                    {
                        l2->sign = 1;
                        list_subtraction(l2, l1);
                    }
                case 1:
                    l2->sign = 0;
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list_addition(l1, l2);
                    }
                    else
                    {
                        list_addition(l2, l1);
                    }
                case 2:
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list_addition(l1, l2);
                    }
                    else
                    {
                        l2->sign = 1;
                        list_addition(l2, l1);
                    }
                case 3:
                    l2->sign = 0;
                    if (compare_lists(l1, l2) >= 0)
                    {
                        list_subtraction(l1, l2);
                    }
                    else
                    {
                        list_subtraction(l2, l1);
                    }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}