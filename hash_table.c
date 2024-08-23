#include "hash_table.h"
#include "bst.h"
#include "komihash.h"
#include <stdlib.h>
#include <string.h>

static uint64_t INIT_SEED = 0;

static uint64_t get_seed()
{
    return komirand(&INIT_SEED, &INIT_SEED);
}

hash_table *ht_new(size_t capacity)
{
    if (capacity < MIN_CAPACITY || capacity > MAX_CAPACITY)
        return NULL;

    hash_table *ht = malloc(sizeof(struct hash_table));
    ht->capacity = capacity;
    ht->len = 0;
    ht->seed = get_seed();
    ht->lookup_table = malloc(capacity * sizeof(struct bst *));

    for (size_t i = 0; i < ht->capacity; i++)
        ht->lookup_table[i] = NULL;

    return ht;
}

void ht_free(hash_table *ht)
{
    for (size_t i = 0; i < ht->capacity; i++)
    {
        if (ht->lookup_table[i])
            bst_free(ht->lookup_table[i]);
    }

    free(ht->lookup_table);
    free(ht);
}

static size_t ht_get_lookup_table_index(hash_table *ht, char *key)
{
    size_t hash = (size_t)komihash((void *)key, sizeof(key), ht->seed);
    return hash % ht->capacity;
}

void ht_set(hash_table *ht, char *key, char *value)
{
    size_t index = ht_get_lookup_table_index(ht, key);

    if (!ht->lookup_table[index])
        ht->lookup_table[index] = bst_new();

    bst *key_tree = ht->lookup_table[index];

    if (!bst_find(key_tree, key))
    {
        bst_insert(key_tree, key, value);
        ht->len++;
    }
    else
        bst_update(key_tree, key, value);
}

char *ht_get(hash_table *ht, char *key)
{
    size_t index = ht_get_lookup_table_index(ht, key);
    bst *key_tree = ht->lookup_table[index];

    if (!key_tree)
        return NULL;

    bst_node *node = bst_find(key_tree, key);
    return node ? node->entry->value : NULL;
}

void ht_delete(hash_table *ht, char *key)
{
    size_t index = ht_get_lookup_table_index(ht, key);
    bst *key_tree = ht->lookup_table[index];

    if (!key_tree)
        return;

    bst_delete(key_tree, key);
    ht->len--;
}