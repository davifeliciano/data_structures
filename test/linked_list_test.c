#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void ll_assert_emptiness(linked_list *list) {
    assert(!list->head);
    assert(!list->tail);
    assert(list->len == 0);
}

void ll_assert_null_at_ends(linked_list *list) {
    assert(!list->head->prev);
    assert(!list->tail->next);
}

void test_ll_new() {
    printf("test_ll_new... ");
    linked_list *list = ll_new();
    ll_assert_emptiness(list);
    ll_free(list);
    printf("ok!\n");
}

void test_ll_from_array() {
    printf("test_ll_from_array... ");
    char *empty_array[] = {};
    linked_list *empty_list = ll_from_array(empty_array, 0);
    ll_assert_emptiness(empty_list);
    ll_free(empty_list);
    char *array[] = {"first", "last"};
    linked_list *list = ll_from_array(array, 2);
    assert(list->head && list->tail);
    ll_assert_null_at_ends(list);
    assert(!strcmp(list->head->value, array[0]));
    assert(!strcmp(list->tail->value, array[1]));
    assert(list->head->next == list->tail);
    assert(list->tail->prev == list->head);
    assert(list->len == 2);
    ll_free(list);
    printf("ok!\n");
}

void test_ll_insert_first() {
    printf("test_ll_insert_first... ");
    linked_list *list = ll_new();
    char *first_insert_str = "first";
    ll_node *first_new_node = ll_insert_first(list, first_insert_str);
    ll_assert_null_at_ends(list);
    assert(list->head == list->tail);
    assert(list->head == first_new_node);
    assert(!strcmp(list->head->value, first_insert_str));
    assert(!strcmp(first_new_node->value, first_insert_str));
    assert(list->len == 1);
    char *last_insert_str = "last";
    ll_node *last_new_node = ll_insert_first(list, last_insert_str);
    ll_assert_null_at_ends(list);
    assert(list->head == last_new_node);
    assert(!strcmp(list->head->value, last_insert_str));
    assert(!strcmp(last_new_node->value, last_insert_str));
    assert(list->len == 2);
    ll_free(list);
    printf("ok!\n");
}

void test_ll_insert_last() {
    printf("test_ll_insert_last... ");
    linked_list *list = ll_new();
    char *first_insert_str = "first";
    ll_node *first_new_node = ll_insert_last(list, first_insert_str);
    ll_assert_null_at_ends(list);
    assert(list->head == list->tail);
    assert(list->tail == first_new_node);
    assert(!strcmp(list->tail->value, first_insert_str));
    assert(!strcmp(first_new_node->value, first_insert_str));
    assert(list->len == 1);
    char *last_insert_str = "last";
    ll_node *last_new_node = ll_insert_last(list, last_insert_str);
    ll_assert_null_at_ends(list);
    assert(list->tail == last_new_node);
    assert(!strcmp(list->tail->value, last_insert_str));
    assert(!strcmp(last_new_node->value, last_insert_str));
    assert(list->len == 2);
    ll_free(list);
    printf("ok!\n");
}

void test_ll_insert_at() {
    printf("test_ll_insert_at... ");
    linked_list *list = ll_new();
    char *first_value = "first";
    ll_node *first_node = ll_insert_at(list, 0, first_value);
    assert(first_node == list->head);
    assert(first_node == list->tail);
    assert(!strcmp(first_node->value, first_value));
    assert(list->len == 1);
    char *last_value = "last";
    ll_node *last_node = ll_insert_at(list, 1, last_value);
    assert(last_node == list->tail);
    assert(last_node == first_node->next);
    assert(!strcmp(last_node->value, last_value));
    assert(list->len == 2);
    char *mid_value = "mid";
    ll_node *mid_node = ll_insert_at(list, 1, mid_value);
    assert(mid_node == first_node->next);
    assert(mid_node == last_node->prev);
    assert(mid_node->prev == first_node);
    assert(mid_node->next == last_node);
    assert(!strcmp(mid_node->value, mid_value));
    assert(list->len == 3);
    assert(!ll_insert_at(list, 99, "out_of_bounds"));
    ll_free(list);
    printf("ok!\n");
}

void test_ll_remove_first() {
    printf("test_ll_remove_first... ");
    linked_list *empty_list = ll_new();
    assert(!ll_remove_first(empty_list));
    ll_free(empty_list);
    char *array[] = {"first", "last"};
    linked_list *list = ll_from_array(array, 2);
    char *first_removed = ll_remove_first(list);
    ll_assert_null_at_ends(list);
    assert(!strcmp(first_removed, array[0]));
    assert(list->head == list->tail);
    assert(!strcmp(list->head->value, array[1]));
    assert(list->len == 1);
    free(first_removed);
    char *last_removed = ll_remove_first(list);
    assert(!strcmp(last_removed, array[1]));
    ll_assert_emptiness(list);
    free(last_removed);
    ll_free(list);
    printf("ok!\n");
}

void test_ll_remove_last() {
    printf("test_ll_remove_last... ");
    linked_list *empty_list = ll_new();
    assert(!ll_remove_last(empty_list));
    ll_free(empty_list);
    char *array[] = {"first", "last"};
    linked_list *list = ll_from_array(array, 2);
    char *first_removed = ll_remove_last(list);
    ll_assert_null_at_ends(list);
    assert(!strcmp(first_removed, array[1]));
    assert(list->head == list->tail);
    assert(!strcmp(list->tail->value, array[0]));
    assert(list->len == 1);
    free(first_removed);
    char *last_removed = ll_remove_last(list);
    assert(!strcmp(last_removed, array[0]));
    ll_assert_emptiness(list);
    free(last_removed);
    ll_free(list);
    printf("ok!\n");
}

void test_ll_remove_at() {
    printf("test_ll_remove_at... ");
    linked_list *empty_list = ll_new();
    assert(!ll_remove_at(empty_list, 0));
    ll_free(empty_list);
    char *array[] = {"first", "mid", "last"};
    linked_list *list = ll_from_array(array, 3);
    assert(!ll_remove_at(list, 99));
    char *first_removed = ll_remove_at(list, 1);
    assert(!strcmp(first_removed, array[1]));
    assert(list->head->next == list->tail);
    assert(list->tail->prev == list->head);
    assert(list->len == 2);
    free(first_removed);
    char *second_removed = ll_remove_at(list, 1);
    ll_assert_null_at_ends(list);
    assert(!strcmp(second_removed, array[2]));
    assert(list->head == list->tail);
    assert(list->len == 1);
    free(second_removed);
    char *third_removed = ll_remove_at(list, 0);
    ll_assert_emptiness(list);
    assert(!strcmp(third_removed, array[0]));
    free(third_removed);
    ll_free(list);
    printf("ok!\n");
}

void test_ll_get_at() {
    printf("test_ll_get_at... ");
    char *array[] = {"first", "mid", "last"};
    linked_list *list = ll_from_array(array, 3);
    ll_node *mid = ll_get_at(list, 1);
    ll_node *last = ll_get_at(list, list->len - 1);
    assert(mid == list->head->next);
    assert(last == list->tail);
    assert(!ll_get_at(list, 99));
    ll_free(list);
    printf("ok!\n");
}

void test_ll_set_at() {
    printf("test_ll_set_at... ");
    char *array[] = {"first", "mid", "last"};
    linked_list *list = ll_from_array(array, 3);
    char *updated_mid_value = "updated_mid";
    char *updated_last_value = "updated_last";
    ll_node *updated_mid = ll_set_at(list, 1, updated_mid_value);
    ll_node *updated_last = ll_set_at(list, 2, updated_last_value);
    assert(updated_mid == list->head->next);
    assert(!strcmp(updated_mid->value, updated_mid_value));
    assert(updated_last == list->tail);
    assert(!strcmp(updated_last->value, updated_last_value));
    assert(!ll_set_at(list, 99, "out_of_bounds"));
    ll_free(list);
    printf("ok!\n");
}

void test_ll_find_first() {
    printf("test_ll_find... ");
    linked_list *empty_list = ll_new();
    assert(!ll_find_first(empty_list, "search_term"));
    ll_free(empty_list);
    char *array[] = {"first", "mid", "last"};
    linked_list *list = ll_from_array(array, 3);
    char *search_term = "last";
    ll_node *search_result = ll_find_first(list, search_term);
    assert(search_result == list->tail);
    assert(!strcmp(search_result->value, search_term));
    assert(!ll_find_first(list, "search_term"));
    ll_free(list);
    printf("ok!\n");
}

void test_ll_find_last() {
    printf("test_ll_find_last... ");
    linked_list *empty_list = ll_new();
    assert(!ll_find_last(empty_list, "search_term"));
    ll_free(empty_list);
    char *array[] = {"first", "mid", "last"};
    linked_list *list = ll_from_array(array, 3);
    char *search_term = "first";
    ll_node *search_result = ll_find_last(list, search_term);
    assert(search_result == list->head);
    assert(!strcmp(search_result->value, search_term));
    assert(!ll_find_last(list, "search_term"));
    ll_free(list);
    printf("ok!\n");
}

int main(int argc, char **argv) {
    test_ll_new();
    test_ll_from_array();
    test_ll_insert_first();
    test_ll_insert_last();
    test_ll_insert_at();
    test_ll_remove_first();
    test_ll_remove_last();
    test_ll_remove_at();
    test_ll_get_at();
    test_ll_set_at();
    test_ll_find_first();
    test_ll_find_last();
    return 0;
}