#pragma once

typedef struct node
{
    int value;
    struct node *next;
    struct node *prev;
} node;

typedef struct list
{
    node *first;
    node *last;
    int sign;
} list;

node* node_init(int data);

node* node_delete(node* n);

list* list_make();

void list_add_front(list *ln, int data);

void list_print(list *number);

void list_add_last(list *ln, int data);

void remove_last(list *ln);

list* list_addition(list *l1, list *l2);

list* list_subtraction(list *l1, list *l2);

list* list_mult(list *l1, list *l2);

list* int_to_list(int n);

list *list_delete(list *l);

list* int_mult(list *l1, int n);

int getqout(list *l1, list *l2);

list* list_div(list *l1, list *l2);

int list_len(list *ln);

int compare_lists(list *l1, list *l2);

list* get_list(char c);