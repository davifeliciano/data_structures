#include "bst.h"
#include "komihash.h"
#include <stdlib.h>

#ifndef HASH_TABLE
#define HASH_TABLE

#define MIN_CAPACITY 8
#define MAX_CAPACITY ((size_t) - 1)

typedef struct hash_table {
    size_t capacity;
    size_t len;
    bst **lookup_table;
    uint64_t seed;
} hash_table;

hash_table *ht_new(size_t capacity);
void ht_free(hash_table *ht);
void ht_set(hash_table *ht, char *key, char *value);
char *ht_get(hash_table *ht, char *key);
void ht_delete(hash_table *ht, char *key);

#endif