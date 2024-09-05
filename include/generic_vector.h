#ifndef GENERIC_VECTOR
#define GENERIC_VECTOR

#include <stdlib.h>

#define MIN_CAPACITY 32
#define MAX_CAPACITY ((size_t) - 1)
#define CAPACITY_STEP 32

typedef struct gen_vec {
    size_t capacity;
    size_t len;
    size_t elem_size;
    void **elems;
} gen_vec;

gen_vec *gen_vec_new(size_t elem_size);
gen_vec *gen_vec_new_with_capacity(size_t capacity, size_t elem_size);
void gen_vec_free(gen_vec *vector);
gen_vec *gen_vec_clone(gen_vec *vector);
void *gen_vec_get(gen_vec *vector, size_t index);
void *gen_vec_append(gen_vec *vector, void *value);
void *gen_vec_insert_at(gen_vec *vector, size_t index, void *value);
void *gen_vec_pop(gen_vec *vector);
void *gen_vec_remove(gen_vec *vector, size_t index);
void gen_vec_swap(gen_vec *vector, size_t left, size_t right);

#endif