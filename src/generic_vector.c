#include "generic_vector.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

gen_vec *gen_vec_new(size_t elem_size) {
    gen_vec *vector = malloc(sizeof(struct gen_vec));
    vector->capacity = MIN_CAPACITY;
    vector->len = 0;
    vector->elem_size = elem_size;
    vector->elems = malloc(vector->capacity * vector->elem_size);
    return vector;
};

gen_vec *gen_vec_new_with_capacity(size_t capacity, size_t elem_size) {
    gen_vec *vector = malloc(sizeof(struct gen_vec));
    vector->capacity = capacity;
    vector->len = 0;
    vector->elem_size = elem_size;
    vector->elems = malloc(vector->capacity * vector->elem_size);
    return vector;
}

void gen_vec_free(gen_vec *vector) {
    free(vector->elems);
    free(vector);
};

void *gen_vec_get(gen_vec *vector, size_t index) {
    if (index >= vector->len)
        return NULL;

    return vector->elems[index];
}

static bool gen_vec_grow_if_full(gen_vec *vector) {
    bool vector_is_full = vector->len + 1 > vector->capacity;
    bool vector_cannot_grow = vector->capacity > MAX_CAPACITY - CAPACITY_STEP;

    if (vector_is_full && vector_cannot_grow)
        return false;

    if (vector_is_full) {
        vector->capacity = vector->capacity + CAPACITY_STEP;
        vector->elems = realloc(vector->elems, vector->capacity * sizeof(char *));
    }

    return true;
}

void *gen_vec_append(gen_vec *vector, void *value) {
    if (!gen_vec_grow_if_full(vector))
        return NULL;

    vector->elems[vector->len] = value;
    vector->len++;
    return vector->elems[vector->len - 1];
}

void *gen_vec_insert_at(gen_vec *vector, size_t index, void *value) {
    if (index > vector->len || !gen_vec_grow_if_full(vector))
        return NULL;

    for (size_t i = vector->len; i > index; i--)
        vector->elems[i] = vector->elems[i - 1];

    vector->elems[index] = value;
    vector->len++;
    return vector->elems[index];
}

void *gen_vec_pop(gen_vec *vector) {
    if (!vector->len)
        return NULL;

    void *popped = vector->elems[vector->len - 1];
    vector->elems[vector->len - 1] = NULL;
    vector->len--;
    return popped;
}

void *gen_vec_remove(gen_vec *vector, size_t index) {
    if (index >= vector->len)
        return NULL;

    void *removed = vector->elems[index];

    for (size_t i = index; i < vector->len - 1; i++)
        vector->elems[i] = vector->elems[i + 1];

    vector->elems[vector->len - 1] = NULL;
    vector->len--;
    return removed;
}

void gen_vec_swap(gen_vec *vector, size_t left, size_t right) {
    if (left >= vector->len || right >= vector->len || left == right)
        return;

    void *temp = vector->elems[left];
    vector->elems[left] = vector->elems[right];
    vector->elems[right] = temp;
}
