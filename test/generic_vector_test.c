#include "generic_vector.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 8

void test_gen_vec_append() {
    printf("test_gen_vec_append... ");
    gen_vec *vector = gen_vec_new(sizeof(int *));
    assert(vector->capacity == MIN_CAPACITY);
    assert(vector->len == 0);
    assert(vector->elem_size == sizeof(int *));

    for (size_t i = 0; i < MIN_CAPACITY + 1; i++) {
        int *appended = gen_vec_append(vector, &i);
        assert(*appended == i);
        assert(vector->len == i + 1);
    }

    assert(vector->len == MIN_CAPACITY + 1);
    assert(vector->capacity == MIN_CAPACITY + CAPACITY_STEP);
    gen_vec_free(vector);
    printf("ok!\n");
}

void test_gen_vec_get() {
    printf("test_gen_vec_get... ");
    gen_vec *vector = gen_vec_new(sizeof(char *));

    for (size_t i = 0; i < MIN_CAPACITY + 1; i++) {
        char *value = generate_random_word(WORD_LEN);
        char *appended = gen_vec_append(vector, value);
        char *got = gen_vec_get(vector, i);
        assert(got);
        assert(appended == got);
    }

    char *absent = (char *)gen_vec_get(vector, vector->len);
    assert(!absent);

    for (size_t i = 0; i < vector->len + 1; i++)
        free(gen_vec_get(vector, i));

    gen_vec_free(vector);
    printf("ok!\n");
}

void test_gen_vec_pop() {
    printf("test_gen_vec_pop... ");
    gen_vec *vector = gen_vec_new(sizeof(char *));
    assert(!gen_vec_pop(vector));
    char *value = "appended";
    char *appended = gen_vec_append(vector, value);
    char *popped = gen_vec_pop(vector);
    assert(appended == popped);
    assert(vector->len == 0);
    gen_vec_free(vector);
    printf("ok!\n");
}

void init_rand_vector(gen_vec *vector, size_t len) {
    for (size_t i = 0; i < len; i++) {
        char *value = generate_random_word(WORD_LEN);
        gen_vec_append(vector, value);
    }
}

void test_gen_vec_remove() {
    printf("test_gen_vec_remove... ");
    gen_vec *vector = gen_vec_new(sizeof(char *));
    init_rand_vector(vector, MIN_CAPACITY);
    assert(!gen_vec_remove(vector, vector->len));

    for (size_t i = 0; i < MIN_CAPACITY - 1; i++) {
        size_t old_len = vector->len;
        char *elem = gen_vec_get(vector, 0);
        char *next_elem = gen_vec_get(vector, 1);
        char *removed = gen_vec_remove(vector, 0);
        char *replacer = gen_vec_get(vector, 0);
        assert(elem == removed);
        assert(next_elem == replacer);
        assert(vector->len == old_len - 1);
        free(removed);
    }

    assert(vector->len == 1);
    free(gen_vec_remove(vector, 0));
    assert(!vector->elems[0]);
    assert(vector->len == 0);
    gen_vec_free(vector);
    printf("ok!\n");
}

void test_gen_vec_swap() {
    printf("test_gen_vec_swap... ");
    gen_vec *vector = gen_vec_new(sizeof(char *));
    init_rand_vector(vector, MIN_CAPACITY);
    char *first = gen_vec_get(vector, 0);

    for (size_t i = 0; i < vector->len - 1; i++) {
        char *left = gen_vec_get(vector, i);
        char *right = gen_vec_get(vector, i + 1);
        gen_vec_swap(vector, i, i + 1);
        assert(vector->elems[i] == right);
        assert(vector->elems[i + 1] == left);
    }

    char *last = gen_vec_get(vector, vector->len - 1);
    assert(first == last);

    for (size_t i = 0; i < vector->len; i++)
        free(gen_vec_get(vector, i));

    gen_vec_free(vector);
    printf("ok!\n");
}

int main(int argc, char **argv) {
    test_gen_vec_append();
    test_gen_vec_get();
    test_gen_vec_pop();
    test_gen_vec_remove();
    test_gen_vec_swap();
    return 0;
}