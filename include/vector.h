#include <stdlib.h>

#ifndef VECTOR
#define VECTOR

#define MIN_CAPACITY 32
#define MAX_CAPACITY ((size_t)-1)
#define CAPACITY_STEP 32

typedef struct vec {
    size_t capacity;
    size_t len;
    char **elems;
} vec;

vec *vec_new();
void vec_free(vec *vector);
char *vec_get(vec* vector, size_t index);
char *vec_append(vec* vector, char *value);
char *vec_pop(vec *vector);
char *vec_remove(vec *vector, size_t index);

#endif