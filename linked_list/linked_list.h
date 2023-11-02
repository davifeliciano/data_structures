#include <stdlib.h>

#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct node
{
    char *value;
    struct node *next;
    struct node *prev;
} node;

typedef struct linked_list
{
    struct node *head;
    struct node *tail;
    size_t len;
} linked_list;

linked_list *ll_new();
void ll_free(linked_list *list);
linked_list *ll_from_array(char **arr, size_t len);
node *ll_insert_first(linked_list *list, char *value);
node *ll_insert_last(linked_list *list, char *value);
node *ll_insert_at(linked_list *list, size_t index, char *value);
char *ll_remove_first(linked_list *list);
char *ll_remove_last(linked_list *list);
char *ll_remove_at(linked_list *list, size_t index);
node *ll_get_at(linked_list *list, size_t index);
node *ll_set_at(linked_list *list, size_t index, char *value);
node *ll_find_first(linked_list *list, char *value);
node *ll_find_last(linked_list *list, char *value);
void ll_display(linked_list *list);

#endif
