#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdlib.h>

typedef struct ll_node {
    char *value;
    struct ll_node *next;
    struct ll_node *prev;
} ll_node;

typedef struct linked_list {
    struct ll_node *head;
    struct ll_node *tail;
    size_t len;
} linked_list;

linked_list *ll_new();
void ll_free(linked_list *list);
linked_list *ll_from_array(char **arr, size_t len);
ll_node *ll_insert_first(linked_list *list, char *value);
ll_node *ll_insert_last(linked_list *list, char *value);
ll_node *ll_insert_at(linked_list *list, size_t index, char *value);
char *ll_remove_first(linked_list *list);
char *ll_remove_last(linked_list *list);
char *ll_remove_at(linked_list *list, size_t index);
ll_node *ll_get_at(linked_list *list, size_t index);
ll_node *ll_set_at(linked_list *list, size_t index, char *value);
ll_node *ll_find_first(linked_list *list, char *value);
ll_node *ll_find_last(linked_list *list, char *value);
void ll_display(linked_list *list);

#endif
