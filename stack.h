#pragma once

typedef struct node_stack
{
    list* value;
    struct node_stack *next;
    struct node_stack *prev;
} node_stack;

typedef struct stack
{
    node_stack *last;
} stack;

node_stack* stack_node_init(list *data);

node_stack* stack_node_delete(node_stack* n);

stack* stack_make();

void push(stack *s, list *data);

list* pop(stack *s);