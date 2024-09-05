#ifndef BINARY_HEAP
#define BINARY_HEAP

#include "generic_vector.h"

typedef struct bin_heap {
    gen_vec *vector;
} bin_heap;

typedef struct bin_heap_entry {
    double priority;
    void *value;
} bin_heap_entry;

bin_heap *bin_heap_new();

#endif