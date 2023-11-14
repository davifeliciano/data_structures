#include <stdbool.h>

#ifndef BST
#define BST

typedef struct bst
{
    struct bst_node *root;
} bst;

typedef struct bst_node
{
    struct bst_node *parent;
    struct bst_node *left;
    struct bst_node *right;
    struct bst_entry *entry;
} bst_node;

typedef struct bst_entry
{
    char *key;
    char *value;
} bst_entry;

bst *bst_new();
void bst_free(bst *tree);
bst_node *bst_subtree_first(bst_node *node);
bst_node *bst_subtree_last(bst_node *node);
bst_node *bst_successor(bst_node *node);
bst_node *bst_predecessor(bst_node *node);
bst_node *bst_find(bst *tree, char *key);
bst_node *bst_insert(bst *tree, char *key, char *value);
bst_node *bst_update(bst *tree, char *key, char *value);
void bst_delete(bst *tree, char *key);
void bst_display_keys(bst *tree);

#endif
