#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_vec_append() {
    printf("test_vec_append... ");
    vec *vector = vec_new();
    assert(vector->capacity == MIN_CAPACITY);
    assert(vector->len == 0);

    for (size_t i = 0; i < MIN_CAPACITY + 1; i++)
    {
        char value = (char) i;
        char *appended = vec_append(vector, &value);
        assert(!strcmp(appended, &value));
        assert(!strcmp(appended, vector->elems[i]));
        assert(vector->len == i + 1);
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
        char value = (char) i;
        char *appended = vec_append(vector, &value);
        char *got = vec_get(vector, i);
        assert(got);
        assert(appended == got);
    }

    char *absent = vec_get(vector, vector->len);
    assert(!absent);
    vec_free(vector);
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

void test_vec_remove() {
    printf("test_vec_remove... ");
    vec *vector = vec_new();

    for (size_t i = 0; i < MIN_CAPACITY; i++) {
        char value = (char) i;
        vec_append(vector, &value);
    }

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

int main(int argc, char **argv)
{
    test_vec_append();
    test_vec_get();
    test_vec_pop();
    test_vec_remove();
    return 0;
}