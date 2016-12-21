#include <stdio.h>
#include <stdlib.h>
#include "num_list.h"
#include "stack.h"

node* node_init(int data)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->value = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

node* node_delete(node* n)
{
    free (n);
    n = NULL;
    return n;
}

list* list_make()
{
    list *new_list = (list *)malloc(sizeof(list));
    new_list->first = NULL;
    new_list->last = NULL;
    new_list->sign = 0;
    return new_list;
}

void list_add_front(list *ln, int data)
{
    node *new_node = node_init(data);
    if (ln->first == NULL)
    {
        ln->first = new_node;
        ln->last = new_node;
    }
    else 
    {
        ln->first->prev = new_node;
        new_node->next = ln->first;
        ln->first = new_node;
    }
    return;
}

void list_print(list *number)
{
    node *curr = number->last;
    if (number->sign != 0)
    {
        printf("%c", '-');
    }
    while (curr)
    {
        printf("%d", curr->value);
        curr = curr->prev;
    }
    puts("");
}

void list_add_last(list *ln, int data)
{
    node *new_node = node_init(data);
    if (ln->first == NULL)
    {
        ln->first = new_node;
        ln->last = new_node;
    }
    else
    {
        ln->last->next = new_node;
        new_node->prev = ln->last;
        ln->last = new_node;
    }
}

list* get_list(char c)
{
    list *ln = list_make();
    list_add_front(ln, c - 48);
    while ((c = fgetc(stdin)) != '\n')
    {
        if (c == '-')
        {
            ln->sign = 1;
        }
        else 
        {
            list_add_front(ln, c - 48);
        }
    }
    return ln;
}

void remove_last(list *ln)
{
    ln->last = ln->last->prev;
    node_delete(ln->last->next);
    ln->last->next = NULL;
}

int list_len(list *ln)
{
    int len = 0;
    node *digit = ln->first;
    while (digit != NULL)
    {
        len++;
        digit = digit->next;
    }
    return len;
}

list* list_addition(list *l1, list *l2)
{
    node *curr1 = l1->first;
    node *curr2 = l2->first;
    int add = 0;
    while (curr2 != NULL)
    {
        curr1->value += add;
        curr1->value = curr1->value + curr2->value;
        add = curr1->value / 10;
        curr1->value = curr1->value % 10;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    if (add != 0)
    {
        if (curr1 == NULL)
        {
            list_add_last(l1, add);
        }
        else
        {
            while (curr1 != NULL && add != 0)
            {
                curr1->value += add;
                add = curr1->value / 10;
                curr1->value = curr1->value % 10;
                curr1 = curr1->next;
            }
            if (curr1 == NULL)
            {
                list_add_last(l1, add);
            }
        }
    }
    if (l1->last->value == 0)
    {
        remove_last(l1);
    }
    return l1;
}

list* list_subtraction(list *l1, list *l2)
{
    node *curr1 = l1->first;
    node *curr2 = l2->first;
    int add = 0;
    while (curr2 != NULL)
    {
        curr1->value += add;
        add = 0;
        curr1->value = curr1->value - curr2->value;
        if (curr1->value < 0)
        {
            add = -1;
            curr1->value += 10;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    while (add != 0 && curr1 != NULL)
    {
        curr1->value += add;
        if (curr1->value < 0)
        {
            add = -1;
            curr1->value +=10;
        }
        curr1 = curr1->next;
    }
    if (list_len(l1) == 1 && l1->first->value == 0 && l1->last->value == 0)
    {
        l1->sign = 0;
        return l1;
    }
    while (l1->last->value == 0)
    {
        remove_last(l1);
    }
    return(l1);
}

list* list_mult(list *l1, list *l2)
{
    list *result = list_make();
    node *curr1 = l1->first;
    node *curr2 = l2->first;
    while (curr1 || curr2)
    {
        if (curr1)
        {
            curr1 = curr1->next;
            list_add_last(result, 0);
        }
        if (curr2)
        {
            curr2 = curr2->next;
            list_add_last(result, 0);
        }
    }
    curr1 = l1->first;
    curr2 = l2->first;
    node *curr_result = result->first;
    node *prev_result = result->first;
    while (curr2)
    {
        while (curr1)
        {
            curr_result->value += curr1->value * curr2->value;
            curr1 = curr1->next;
            curr_result = curr_result->next;
        }
        prev_result = prev_result->next;
        curr_result = prev_result;
        curr1 = l1->first;
        curr2 = curr2->next;
    }
    node *curr_num = result->first;
    while(curr_num->next)
    {
        if (curr_num->value >= 10)
        {
            curr_num->next->value += curr_num->value / 10;
            curr_num->value %= 10;
        }
        curr_num = curr_num->next;
    }
    while (result->last->value == 0)
    {
        remove_last(result);
    }
    return result;
}

list* int_to_list(int n)
{
    list *lc = list_make();
    list_add_last(lc, n % 10);
    n = n / 10;
    while (n > 0)
    {
        list_add_last(lc, n % 10);
        n = n / 10;
    }
    return lc;
}

list *list_delete(list *l)
{
    node *curr = l->first;
    while (curr)
    {
        if (curr->next)
        {
            curr = curr->next;
            curr->prev = node_delete(curr->prev);
        }
        else
        {
            curr = node_delete(curr);
        }
    }
    free(l);
    l = NULL;
    return l;
}

list* int_mult(list *l1, int n)
{
    list *l2 = int_to_list(n);
    list *result = list_mult(l1, l2);
    l2 = list_delete(l2);
    return result;
}

int getqout(list *l1, list *l2)
{
    int qout = 0;
    for (qout = 0; qout < 10; qout++)
    {
        if ((compare_lists(int_mult(l2, qout), l1) <= 0)
            && (compare_lists(int_mult(l2, qout + 1), l1) > 0))
        {
            return qout;
        }
    }
    return 1;
}

list* list_div(list *l1, list *l2)
{
    list *result = list_make();
    if (compare_lists(l1, l2) < 0)
    {
        list_add_last(result, 0);
        return result;
    }
    
    list *subres = list_make();
    list_add_front(subres, l1->last->value);
    
    node *l1_curr = l1->last;
    
    while (compare_lists(subres, l2) < 0)
    {
        l1_curr = l1_curr->prev;
        list_add_front(subres, l1_curr->value);
    }
    
    do 
    {
        int q = getqout(subres, l2);
        list_add_front(result, q);
        subres = list_subtraction(subres, int_mult(l2, q));
        l1_curr = l1_curr->prev;
        if (l1_curr != NULL)
        {
            list_add_front(subres, l1_curr->value);
        }
    }
    while(l1_curr != NULL);
    subres = list_delete(subres);
    return result;
}

int compare_lists(list *l1, list *l2)
{
    int delta = list_len(l1) - list_len(l2);
    if (delta != 0)
    {
        if (delta > 0)
        {
            delta = 1;
        }
        else 
        {
            delta = -1;
        }
        return delta;
    }
    node *curr1 = l1->last;
    node *curr2 = l2->last;
    while (curr1 && curr2 && curr1->value == curr2->value)
    {
        curr1 = curr1->prev;
        curr2 = curr2->prev;
    }
    if (!curr1 && !curr2)
    {
        return 0;
    }
    else if (!curr1 && curr2)
    {
        return -1;
    }
    else if (curr1 && !curr2)
    {
        return 1;
    }
    if (curr1->value < curr2->value)
    {
        delta = -1;
    }
    else if (curr1->value > curr2->value)
    {
        delta = 1;
    }
    return delta;
}

