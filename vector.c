#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

vec *vec_new() {
    vec *vector = malloc(sizeof(struct vec));
    vector->capacity = MIN_CAPACITY;
    vector->len = 0;
    vector->elems = malloc(vector->capacity * sizeof(char *));
    return vector;
};

void vec_free(vec *vector) {
    for (size_t i = 0; i < vector->len; i++)
        free(vector->elems[i]);

    free(vector->elems);
    free(vector);
};

vec *vec_clone(vec *vector) {
    vec *clone = vec_new();
    clone->capacity = vector->capacity;
    clone->len = vector->len;
    clone->elems = realloc(clone->elems, vector->capacity * sizeof(char *));

    for (size_t i = 0; i < vector->len; i++)
        clone->elems[i] = strdup(vector->elems[i]);

    return clone;
}

char *vec_get(vec* vector, size_t index) {
    if (index >= vector->len)
        return NULL;

    return vector->elems[index];
}

char *vec_append(vec* vector, char *value) {
    bool vector_is_full = vector->len + 1 > vector->capacity;
    bool vector_cannot_grow = vector->capacity > MAX_CAPACITY - CAPACITY_STEP;

    if (vector_is_full && vector_cannot_grow)
        return NULL;

    if (vector_is_full) {
        vector->capacity = vector->capacity + CAPACITY_STEP;
        vector->elems = realloc(vector->elems, vector->capacity * sizeof(char *));
    }

    vector->elems[vector->len] = strdup(value);
    vector->len++;
    return vector->elems[vector->len - 1];
}

char *vec_pop(vec *vector) {
    if (!vector->len)
        return NULL;

    char *popped = vector->elems[vector->len - 1];
    vector->elems[vector->len - 1] = NULL;
    vector->len--;
    return popped;
}

char *vec_remove(vec *vector, size_t index) {
    if (index >= vector->len)
        return NULL;

    char *removed = vector->elems[index];

    for (size_t i = index; i < vector->len - 1; i++)
        vector->elems[i] = vector->elems[i + 1];

    vector->elems[vector->len - 1] = NULL;
    vector->len--;
    return removed;
}

void vec_display(vec *vector) {
    if (vector->len == 0) {
        printf("[]\n");
        return;
    }

    printf("[");

    for (size_t i = 0; i < vector->len - 1; i++)
        printf("%s, ", vec_get(vector, i));

    printf("%s]\n", vec_get(vector, vector->len - 1));
}

static void vec_swap(vec *vector, size_t left, size_t right) {
    if (left >= vector->len || right >= vector->len || left == right)
        return;

    char *temp = vector->elems[left];
    vector->elems[left] = vector->elems[right];
    vector->elems[right] = temp;
}

static size_t vec_min_index_at_range(vec *vector, size_t left, size_t right) {
    if (left == right)
        return left;

    size_t min_index = left;

    for (size_t i = left; i <= right; i++) {
        if (strcmp(vector->elems[i], vector->elems[min_index]) < 0)
            min_index = i;
    }

    return min_index;
}

void vec_selection_sort(vec *vector) {
    for (size_t left = 0; left < vector->len; left++) {
        size_t min_index = vec_min_index_at_range(vector, left, vector->len - 1);
        vec_swap(vector, left, min_index);
    }
}
