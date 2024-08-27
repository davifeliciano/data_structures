#include "vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vec *vec_new() {
    vec *vector = malloc(sizeof(struct vec));
    vector->capacity = MIN_CAPACITY;
    vector->len = 0;
    vector->elems = malloc(vector->capacity * sizeof(char *));
    return vector;
};

vec *vec_new_with_capacity(size_t capacity) {
    vec *vector = malloc(sizeof(struct vec));
    vector->capacity = capacity;
    vector->len = 0;
    vector->elems = malloc(vector->capacity * sizeof(char *));
    return vector;
}

void vec_free(vec *vector) {
    for (size_t i = 0; i < vector->len; i++)
        free(vector->elems[i]);

    free(vector->elems);
    free(vector);
};

vec *vec_clone(vec *vector) {
    vec *clone = vec_new_with_capacity(vector->capacity);
    clone->len = vector->len;

    for (size_t i = 0; i < vector->len; i++)
        clone->elems[i] = strdup(vector->elems[i]);

    return clone;
}

char *vec_get(vec *vector, size_t index) {
    if (index >= vector->len)
        return NULL;

    return vector->elems[index];
}

char *vec_append(vec *vector, char *value) {
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

void vec_insertion_sort(vec *vector) {
    for (int i = 1; i < vector->len; i++) {
        char *key = vector->elems[i];
        int j = i - 1;

        while (j >= 0 && strcmp(vector->elems[j], key) > 0) {
            vector->elems[j + 1] = vector->elems[j];
            j--;
        }

        vector->elems[j + 1] = key;
    }
}

static void vec_merge(vec *vector, size_t start, size_t middle, size_t end) {
    size_t left_len = middle - start;
    size_t right_len = end - middle;
    vec *left = vec_new_with_capacity(left_len);
    vec *right = vec_new_with_capacity(right_len);
    left->len = left_len;
    right->len = right_len;

    for (size_t i = 0; i < left->len; i++)
        left->elems[i] = vector->elems[start + i];

    for (size_t i = 0; i < right->len; i++)
        right->elems[i] = vector->elems[middle + i];

    size_t i = 0;
    size_t j = 0;

    for (size_t k = start; k < end; k++) {
        if (j >= right->len || (i < left->len && strcmp(left->elems[i], right->elems[j]) <= 0)) {
            vector->elems[k] = left->elems[i];
            i++;
        } else {
            vector->elems[k] = right->elems[j];
            j++;
        }
    }

    free(left->elems);
    free(left);
    free(right->elems);
    free(right);
}

static void vec_merge_subsort(vec *vector, size_t start, size_t end) {
    if (start == end - 1)
        return;

    size_t middle = (start + end) / 2;
    vec_merge_subsort(vector, start, middle);
    vec_merge_subsort(vector, middle, end);
    vec_merge(vector, start, middle, end);
}

void vec_merge_sort(vec *vector) {
    vec_merge_subsort(vector, 0, vector->len);
}

static size_t vec_partition(vec *vector, size_t start, size_t end) {
    size_t pivot = start;

    for (size_t i = start; i < end - 1; i++) {
        if (strcmp(vector->elems[i], vector->elems[end - 1]) <= 0) {
            vec_swap(vector, i, pivot);
            pivot++;
        }
    }

    vec_swap(vector, pivot, end - 1);
    return pivot;
}

static void vec_quick_subsort(vec *vector, size_t start, size_t end) {
    if (start == end - 1)
        return;

    size_t pivot = vec_partition(vector, start, end);
    vec_quick_subsort(vector, start, pivot);
    vec_quick_subsort(vector, pivot, end);
}

void vec_quick_sort(vec *vector) {
    vec_quick_subsort(vector, 0, vector->len);
}