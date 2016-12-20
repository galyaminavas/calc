#include <stdio.h>
#include <stdlib.h>
#include "num_list.h"
#include "manager.h"

typedef struct stack_node
{
    list *data;
    struct stack_node *prev;
} stack_node;

/*stack_node* stack_node_init(list* l)
{
    stack_node *sn = (stack_node *)malloc(sizeof(stack_node));
    sn->data = l;
    sn->prev = 0;
    return sn;
}*/

/*stack_node* stack_node_delete(stack_node *sn)
{
    if (sn->data)
    {
        
    }
    return sn;
}*/

int main()
{
    list *long_1;
    list *long_2;
    long_1 = get_list();
    long_2 = get_list();
    char to_do;
    to_do = fgetc(stdin);
    operator_switch (to_do, long_1, long_2);
    //long_1 = list_addition(long_1, long_2);
    list_print(long_1);
    list_print(long_2);
    return 0;
}

