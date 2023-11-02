#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

linked_list *ll_new()
{
    linked_list *list = malloc(sizeof(struct linked_list));
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return list;
}

void ll_free(linked_list *list)
{
    node *cur = list->head;

    while (cur)
    {
        node *next = cur->next;
        free(cur->value);
        free(cur);
        cur = next;
    }

    free(list);
}

linked_list *ll_from_array(char **arr, size_t len)
{
    linked_list *list = ll_new();

    for (size_t i = 0; i < len; i++)
        ll_insert_last(list, arr[i]);

    return list;
}

node *ll_insert_first(linked_list *list, char *value)
{
    node *new_node = malloc(sizeof(struct node));
    new_node->value = strdup(value);
    new_node->prev = NULL;
    new_node->next = list->head;

    if (list->head)
        list->head->prev = new_node;

    if (!list->tail)
        list->tail = new_node;

    list->head = new_node;
    list->len++;
    return new_node;
}

node *ll_insert_last(linked_list *list, char *value)
{
    node *new_node = malloc(sizeof(struct node));
    new_node->value = strdup(value);
    new_node->prev = list->tail;
    new_node->next = NULL;

    if (list->tail)
        list->tail->next = new_node;

    if (!list->head)
        list->head = new_node;

    list->tail = new_node;
    list->len++;
    return new_node;
}

node *ll_insert_at(linked_list *list, size_t index, char *value)
{
    if (index > list->len)
        return NULL;

    if (index == 0)
        return ll_insert_first(list, value);

    if (index == list->len)
        return ll_insert_last(list, value);

    node *cur = list->head->next;
    size_t cur_index = 1;

    while (cur)
    {
        if (cur_index == index)
        {
            node *new_node = malloc(sizeof(struct node));
            new_node->value = strdup(value);
            new_node->prev = cur->prev;
            new_node->next = cur;
            cur->prev->next = new_node;
            cur->prev = new_node;
            list->len++;
            return new_node;
        }

        cur = cur->next;
        cur_index++;
    }

    return NULL;
}

char *ll_remove_first(linked_list *list)
{
    if (!list->head)
        return NULL;

    node *head = list->head;
    char *head_value = head->value;
    node *head_next = head->next;

    if (head_next)
        head_next->prev = NULL;
    else
        list->tail = NULL;

    free(head);
    list->head = head_next;
    list->len--;
    return head_value;
}

char *ll_remove_last(linked_list *list)
{
    if (!list->tail)
        return NULL;

    node *tail = list->tail;
    char *tail_value = list->tail->value;
    node *tail_prev = list->tail->prev;

    if (tail_prev)
        tail_prev->next = NULL;
    else
        list->head = NULL;

    free(tail);
    list->tail = tail_prev;
    list->len--;
    return tail_value;
}

char *ll_remove_at(linked_list *list, size_t index)
{
    if (index >= list->len)
        return NULL;

    if (index == 0)
        return ll_remove_first(list);

    if (index == list->len - 1)
        return ll_remove_last(list);

    node *cur = list->head->next;
    size_t cur_index = 1;

    while (cur)
    {
        if (cur_index == index)
        {
            char *removed_value = cur->value;
            cur->prev->next = cur->next;

            if (cur->next)
                cur->next->prev = cur->prev;

            free(cur);
            list->len--;
            return removed_value;
        }

        cur = cur->next;
        cur_index++;
    }

    return NULL;
}

node *ll_get_at(linked_list *list, size_t index)
{
    if (index >= list->len)
        return NULL;

    node *cur = list->head;
    size_t cur_index = 0;

    while (cur)
    {
        if (cur_index == index)
            return cur;

        cur = cur->next;
        cur_index++;
    }
}

node *ll_set_at(linked_list *list, size_t index, char *value)
{
    if (index >= list->len)
        return NULL;

    node *cur = list->head;
    size_t cur_index = 0;

    while (cur)
    {
        if (cur_index == index)
        {
            free(cur->value);
            cur->value = strdup(value);
            return cur;
        }

        cur = cur->next;
        cur_index++;
    }
}

node *ll_find_first(linked_list *list, char *value)
{
    if (!list->head)
        return NULL;

    node *cur = list->head;

    while (cur)
    {
        if (!strcmp(value, cur->value))
            return cur;

        cur = cur->next;
    }

    return NULL;
}

node *ll_find_last(linked_list *list, char *value)
{
    if (!list->tail)
        return NULL;

    node *cur = list->tail;

    while (cur)
    {
        if (!strcmp(value, cur->value))
            return cur;

        cur = cur->prev;
    }

    return NULL;
}

void ll_display(linked_list *list)
{
    node *cur = list->head;

    if (!cur)
    {
        printf("[]\n");
        return;
    }

    printf("[");

    while (cur->next)
    {
        printf("%s, ", cur->value);
        cur = cur->next;
    }

    printf("%s]\n", cur->value);
}