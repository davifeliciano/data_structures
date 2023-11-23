#include "hash_table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_UINT64_T ((uint64_t)-1)

void assert_ht_lookup_table_emptiness(hash_table *ht)
{
    for (size_t i = 0; i < ht->capacity; i++)
        assert(!ht->lookup_table[i]);
}

void assert_ht_emptiness(hash_table *ht)
{
    for (size_t i = 0; i < ht->capacity; i++)
        assert(!ht->lookup_table[i] || !ht->lookup_table[i]->root);
}

char *generate_random_word(size_t word_len)
{
    char *word = malloc((word_len + 1) * sizeof(char));

    for (size_t i = 0; i < word_len; i++)
        word[i] = (char)(26 * (rand() / (RAND_MAX + 1.0)) + 97);

    word[word_len] = '\0';
    return word;
}

char **generate_random_word_list(size_t len, size_t word_len)
{
    srand(time(NULL));
    char **word_list = malloc(len * sizeof(char *));

    for (size_t i = 0; i < len; i++)
        word_list[i] = generate_random_word(word_len);

    return word_list;
}

void free_random_word_list(char **word_list, size_t len)
{
    for (size_t i = 0; i < len; i++)
        free(word_list[i]);

    free(word_list);
}

void test_ht_new()
{
    printf("test_ht_new... ");
    size_t capacity = MIN_CAPACITY;
    hash_table *ht = ht_new(capacity);
    assert_ht_lookup_table_emptiness(ht);
    assert(ht->capacity == capacity);
    assert(ht->len == 0);
    assert(ht->seed <= MAX_UINT64_T);
    ht_free(ht);
    printf("ok!\n");
}

void test_ht_interface()
{
    printf("test_ht_interface... ");
    size_t capacity = MIN_CAPACITY;
    hash_table *ht = ht_new(capacity);
    size_t insertions = capacity * capacity;
    size_t word_length = 8;
    char **keys_list = generate_random_word_list(insertions, word_length);
    char **values_list = generate_random_word_list(insertions, word_length);

    for (size_t i = 0; i < insertions; i++)
    {
        ht_set(ht, keys_list[i], values_list[i]);
        assert(!strcmp(ht_get(ht, keys_list[i]), values_list[i]));
    }

    for (size_t i = 0; i < insertions; i++)
    {
        ht_set(ht, keys_list[i], values_list[insertions - i - 1]);
        assert(!strcmp(ht_get(ht, keys_list[i]), values_list[insertions - i - 1]));
    }

    for (size_t i = 0; i < insertions; i++)
        ht_delete(ht, keys_list[i]);

    assert_ht_emptiness(ht);
    assert(ht->len == 0);

    free_random_word_list(keys_list, insertions);
    free_random_word_list(values_list, insertions);
    ht_free(ht);
    printf("ok!\n");
}

int main(int argc, char **argv)
{
    test_ht_new();
    test_ht_interface();
    return 0;
}