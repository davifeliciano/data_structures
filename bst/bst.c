#include "bst.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bst *bst_new()
{
    bst *tree = malloc(sizeof(struct bst));
    tree->root = NULL;
    return tree;
}

static bst_entry *bst_entry_new(char *key, char *value)
{
    bst_entry *entry = malloc(sizeof(struct bst_entry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    return entry;
}

static void bst_entry_free(bst_entry *entry)
{
    free(entry->key);
    free(entry->value);
    free(entry);
}

static void bst_node_free(bst_node *node)
{
    bst_entry_free(node->entry);
    free(node);
}

static void bst_subtree_free(bst_node *node)
{
    if (!node)
        return;

    bst_subtree_free(node->left);
    bst_subtree_free(node->right);
    bst_node_free(node);
}

void bst_free(bst *tree)
{
    bst_subtree_free(tree->root);
    free(tree);
}

bst_node *bst_subtree_first(bst_node *node)
{
    if (!node)
        return NULL;

    return node->left ? bst_subtree_first(node->left) : node;
}

bst_node *bst_subtree_last(bst_node *node)
{
    if (!node)
        return NULL;

    return node->right ? bst_subtree_last(node->right) : node;
}

bst_node *bst_successor(bst_node *node)
{
    if (!node)
        return NULL;

    if (node->right)
        return bst_subtree_first(node->right);

    bst_node *cur = node;

    while (cur->parent)
    {
        if (cur == cur->parent->left)
            return cur->parent;

        cur = cur->parent;
    }

    return NULL;
}

bst_node *bst_predecessor(bst_node *node)
{
    if (!node)
        return NULL;

    if (node->left)
        return bst_subtree_last(node->left);

    bst_node *cur = node;

    while (cur->parent)
    {
        if (cur == cur->parent->right)
            return cur->parent;

        cur = cur->parent;
    }

    return NULL;
}

static bst_node *bst_subtree_insert_after(bst_node *node, bst_entry *entry)
{
    bst_node *new = malloc(sizeof(struct bst_node));
    new->left = NULL;
    new->right = NULL;
    new->entry = entry;

    if (!node->right)
    {
        new->parent = node;
        node->right = new;
    }
    else
    {
        bst_node *subtree_first = bst_subtree_first(node->right);
        new->parent = subtree_first;
        subtree_first->left = new;
    }

    return new;
}

static bst_node *bst_subtree_insert_before(bst_node *node, bst_entry *entry)
{
    bst_node *new = malloc(sizeof(struct bst_node));
    new->left = NULL;
    new->right = NULL;
    new->entry = entry;

    if (!node->left)
    {
        new->parent = node;
        node->left = new;
    }
    else
    {
        bst_node *subtree_last = bst_subtree_last(node->left);
        new->parent = subtree_last;
        subtree_last->right = new;
    }

    return new;
}

static bst_node *bst_find_max_leq_key(bst_node *node, char *key)
{
    if (!node)
        return NULL;

    int cmp_result = strcmp(node->entry->key, key);

    if (cmp_result == 0)
        return node;

    if (cmp_result < 0)
    {
        bst_node *successor = bst_successor(node);
        return (!successor || strcmp(successor->entry->key, key) > 0)
                   ? node
                   : bst_find_max_leq_key(successor, key);
    }

    bst_node *predecessor = bst_predecessor(node);
    return bst_find_max_leq_key(predecessor, key);
}

static bst_node *bst_find_eq_key(bst_node *node, char *key)
{
    if (!node)
        return NULL;

    int cmp_result = strcmp(node->entry->key, key);

    if (cmp_result == 0)
        return node;

    if (cmp_result < 0 && node->right)
        return bst_find_eq_key(node->right, key);

    if (cmp_result > 0 && node->left)
        return bst_find_eq_key(node->left, key);

    return NULL;
}

bst_node *bst_find(bst *tree, char *key)
{
    return bst_find_eq_key(tree->root, key);
}

bst_node *bst_insert(bst *tree, char *key, char *value)
{
    if (!tree->root)
    {
        bst_node *new = malloc(sizeof(struct bst_node));
        new->parent = NULL;
        new->left = NULL;
        new->right = NULL;
        new->entry = bst_entry_new(key, value);
        tree->root = new;
        return new;
    }

    bst_node *max_leq_key_node = bst_find_max_leq_key(tree->root, key);

    if (!max_leq_key_node)
    {
        bst_node *first = bst_subtree_first(tree->root);
        bst_entry *entry = bst_entry_new(key, value);
        return bst_subtree_insert_before(first, entry);
    }

    if (!strcmp(max_leq_key_node->entry->key, key))
        return NULL;

    bst_entry *entry = bst_entry_new(key, value);
    return bst_subtree_insert_after(max_leq_key_node, entry);
}

bst_node *bst_update(bst *tree, char *key, char *value)
{
    bst_node *node = bst_find(tree, key);

    if (!node)
        return NULL;

    free(node->entry->value);
    node->entry->value = strdup(value);
    return node;
}

static bool bst_node_is_leaf(bst_node *node)
{
    return node && !node->left && !node->right;
}

static void bst_remove_leaf(bst_node *node)
{
    if (!bst_node_is_leaf(node))
        return;

    if (node->parent && node->parent->left == node)
        node->parent->left = NULL;

    if (node->parent && node->parent->right == node)
        node->parent->right = NULL;

    bst_node_free(node);
}

static void bst_delete_node(bst_node *node)
{
    if (!node)
        return;

    if (bst_node_is_leaf(node))
        return bst_remove_leaf(node);

    if (node->left)
    {
        bst_node *predecessor = bst_predecessor(node);
        bst_entry *tmp = node->entry;
        node->entry = predecessor->entry;
        predecessor->entry = tmp;
        return bst_delete_node(predecessor);
    }
    else
    {
        bst_node *successor = bst_successor(node);
        bst_entry *tmp = node->entry;
        node->entry = successor->entry;
        successor->entry = tmp;
        return bst_delete_node(successor);
    }
}

void bst_delete(bst *tree, char *key)
{
    if (!tree->root)
        return;

    bst_node *node = bst_find(tree, key);
    bool is_last_element = node == tree->root && bst_node_is_leaf(node);
    bst_delete_node(node);

    if (is_last_element)
        tree->root = NULL;
}

static void bst_subtree_display_keys(bst_node *node, char *prefix)
{
    if (!node)
    {
        printf("%s└⦰\n", prefix);
        return;
    }

    printf("%s└── %s\n", prefix, node->entry->key);
    char *next_prefix = malloc((strlen(prefix) + 5));
    sprintf(next_prefix, "%s%s", prefix, "    ");
    bst_subtree_display_keys(node->left, next_prefix);
    bst_subtree_display_keys(node->right, next_prefix);
    free(next_prefix);
}

void bst_display_keys(bst *tree)
{
    bst_subtree_display_keys(tree->root, "");
}