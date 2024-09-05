#ifndef VECTOR
#define VECTOR

#include <stdlib.h>

#define MIN_CAPACITY 32
#define MAX_CAPACITY ((size_t) - 1)
#define CAPACITY_STEP 32

typedef struct vec {
    size_t capacity;
    size_t len;
    char **elems;
} vec;

vec *vec_new();
vec *vec_new_with_capacity(size_t capacity);
void vec_free(vec *vector);
vec *vec_clone(vec *vector);
char *vec_get(vec *vector, size_t index);
char *vec_append(vec *vector, char *value);
char *vec_insert_at(vec *vector, size_t index, char *value);
char *vec_pop(vec *vector);
char *vec_remove(vec *vector, size_t index);
void vec_display(vec *vector);
void vec_selection_sort(vec *vector);
void vec_insertion_sort(vec *vector);
void vec_merge_sort(vec *vector);
void vec_quick_sort(vec *vector);

#endif