#include <stdio.h>
#include <stdlib.h>
#include "num_list.h"
#include "stack.h"
#include "manager.h"

node_stack* stack_node_init(list *data)
{
    node_stack *new_node = (node_stack *)malloc(sizeof(node_stack));
    new_node->value = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

node_stack* stack_node_delete(node_stack* n)
{
    free (n);
    n = NULL;
    return n;
}

stack* stack_make()
{
    stack *new_stack = (stack *)malloc(sizeof(stack));
    new_stack->last = NULL;
    return new_stack;
}

void push(stack *s, list *data)
{
    node_stack *new_node = stack_node_init(data);
    if (s->last == NULL)
    {
        s->last = new_node;
    }
    else
    {
        s->last->next = new_node;
        new_node->prev = s->last;
        s->last = new_node;
    }
    return;
}

list* pop(stack *s)
{
    list *p = s->last->value;
    if (s->last->prev)
    {
        s->last = s->last->prev;
        stack_node_delete(s->last->next);
    }
    else
    {
        stack_node_delete(s->last);
        s->last = NULL;
    }
    //else if (s->last)
    //{
        //stack_node_delete(s->last);
    //}
    return p;
}

list* pick(stack *s)
{
    list *p = s->last->value;
    return p;
}

