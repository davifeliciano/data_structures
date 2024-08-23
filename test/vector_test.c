#include "vector.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 8

void test_vec_append() {
    printf("test_vec_append... ");
    vec *vector = vec_new();
    assert(vector->capacity == MIN_CAPACITY);
    assert(vector->len == 0);

    for (size_t i = 0; i < MIN_CAPACITY + 1; i++)
    {
        char *value = generate_random_word(WORD_LEN);
        char *appended = vec_append(vector, value);
        assert(!strcmp(appended, value));
        assert(!strcmp(appended, vector->elems[i]));
        assert(vector->len == i + 1);
        free(value);
    }

    assert(vector->len == MIN_CAPACITY + 1);
    assert(vector->capacity == MIN_CAPACITY + CAPACITY_STEP);
    vec_free(vector);
    printf("ok!\n");
}

void test_vec_get() {
    printf("test_vec_get... ");
    vec *vector = vec_new();

    for (size_t i = 0; i < MIN_CAPACITY + 1; i++) {
        char *value = generate_random_word(WORD_LEN);
        char *appended = vec_append(vector, value);
        char *got = vec_get(vector, i);
        assert(got);
        assert(appended == got);
        free(value);
    }

    char *absent = vec_get(vector, vector->len);
    assert(!absent);
    vec_free(vector);
    printf("ok!\n");
}

void test_vec_clone() {
    printf("test_vec_clone... ");
    vec *vector = vec_new();

    for (size_t i = 0; i < MIN_CAPACITY + 1; i++) {
        char *value = generate_random_word(WORD_LEN);
        vec_append(vector, value);
        free(value);
    }

    vec *clone = vec_clone(vector);
    assert(clone->capacity == vector->capacity);
    assert(clone->len == vector->len);

    for (size_t i = 0; i < clone->len; i++) {
        char *vector_elem = vec_get(vector, i);
        char *clone_elem = vec_get(clone, i);
        assert(!strcmp(vector_elem, clone_elem));
    }

    vec_free(vector);
    vec_free(clone);
    printf("ok!\n");
}

void test_vec_pop() {
    printf("test_vec_pop... ");
    vec *vector = vec_new();
    assert(!vec_pop(vector));
    char *value = "appended";
    char *appended = vec_append(vector, value);
    char *popped = vec_pop(vector);
    assert(appended == popped);
    assert(vector->len == 0);
    free(popped);
    vec_free(vector);
    printf("ok!\n");
}

void init_rand_vector(vec *vector, size_t len) {
    for (size_t i = 0; i < len; i++) {
        char *value = generate_random_word(WORD_LEN);
        vec_append(vector, value);
        free(value);
    }
}

void test_vec_remove() {
    printf("test_vec_remove... ");
    vec *vector = vec_new();
    init_rand_vector(vector, MIN_CAPACITY);
    assert(!vec_remove(vector, vector->len));

    for (size_t i = 0; i < MIN_CAPACITY - 1; i++) {
        size_t old_len = vector->len;
        char *elem = vec_get(vector, 0);
        char *next_elem = vec_get(vector, 1);
        char *removed = vec_remove(vector, 0);
        char *replacer = vec_get(vector, 0);
        assert(elem == removed);
        assert(next_elem == replacer);
        assert(vector->len == old_len - 1);
        free(removed);
    }

    assert(vector->len == 1);
    free(vec_remove(vector, 0));
    assert(!vector->elems[0]);
    assert(vector->len == 0);
    vec_free(vector);
    printf("ok!\n");
}

void assert_vector_is_sorted(vec *vector) {
    for (size_t i = 0; i < vector->len - 1; i++)
        assert(strcmp(vec_get(vector, i), vec_get(vector, i + 1)) <= 0);
}

void test_vec_selection_sort() {
    printf("test_vec_selection_sort... ");
    vec *vector = vec_new();
    init_rand_vector(vector, MIN_CAPACITY);
    vec *sorted = vec_clone(vector);
    vec_selection_sort(sorted);
    assert_vector_is_sorted(sorted);
    vec_free(vector);
    vec_free(sorted);
    printf("ok!\n");
}

void test_vec_insertion_sort() {
    printf("test_vec_insertion_sort... ");
    vec *vector = vec_new();
    init_rand_vector(vector, MIN_CAPACITY);
    vec *sorted = vec_clone(vector);
    vec_insertion_sort(sorted);
    assert_vector_is_sorted(sorted);
    vec_free(vector);
    vec_free(sorted);
    printf("ok!\n");
}

int main(int argc, char **argv)
{
    test_vec_append();
    test_vec_get();
    test_vec_clone();
    test_vec_pop();
    test_vec_remove();
    test_vec_selection_sort();
    test_vec_insertion_sort();
    return 0;
}