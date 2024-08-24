#include "bst.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_TREE_SIZE 9
char *keys[] = {"c", "i", "z", "a", "w", "e", "s", "u", "m"};
char *ordered_keys[] = {"a", "c", "e", "i", "m", "s", "u", "w", "z"};
char *value = "value";

void assert_node_order(bst_node *node) {
    if (!node)
        return;

    if (node->left)
        assert(strcmp(node->left->entry->key, node->entry->key) < 0);

    if (node->right)
        assert(strcmp(node->right->entry->key, node->entry->key) > 0);

    assert_node_order(node->left);
    assert_node_order(node->right);
}

void assert_traversal_order(bst *tree) {
    assert_node_order(tree->root);
}

bst *create_test_tree() {
    bst *tree = bst_new();

    for (size_t i = 0; i < TEST_TREE_SIZE; i++) {
        bst_node *inserted = bst_insert(tree, keys[i], value);
        bst_node *found = bst_find(tree, keys[i]);
        assert(inserted == found);
    }

    assert_traversal_order(tree);
    return tree;

    /* expected tree
    c
    └── a
        └⦰
        └⦰
    └── i
        └── e
            └⦰
            └⦰
        └── z
            └── w
                └── s
                    └── m
                        └⦰
                        └⦰
                    └── u
                        └⦰
                        └⦰
                └⦰
            └⦰
    */
}

void test_bst_subtree_first() {
    printf("test_bst_subtree_first... ");
    bst *tree = create_test_tree();
    assert(bst_subtree_first(tree->root) == bst_find(tree, "a"));
    assert(bst_subtree_first(bst_find(tree, "z")) == bst_find(tree, "m"));
    bst_node *leaf = bst_find(tree, "u");
    assert(bst_subtree_first(leaf) == leaf);
    assert(!bst_subtree_first(NULL));
    bst_free(tree);
    printf("ok!\n");
}

void test_bst_subtree_last() {
    printf("test_bst_subtree_last... ");
    bst *tree = create_test_tree();
    assert(bst_subtree_last(tree->root) == bst_find(tree, "z"));
    assert(bst_subtree_last(bst_find(tree, "s")) == bst_find(tree, "u"));
    bst_node *leaf = bst_find(tree, "u");
    assert(bst_subtree_last(leaf) == leaf);
    assert(!bst_subtree_last(NULL));
    bst_free(tree);
    printf("ok!\n");
}

void test_bst_successor() {
    printf("test_bst_successor... ");
    bst *tree = create_test_tree();

    for (size_t i = 0; i < TEST_TREE_SIZE - 1; i++) {
        bst_node *node = bst_find(tree, ordered_keys[i]);
        bst_node *successor = bst_successor(node);
        bst_node *found_successor = bst_find(tree, ordered_keys[i + 1]);
        assert(successor == found_successor);
    }

    assert(!bst_successor(bst_subtree_last(tree->root)));
    assert(!bst_successor(NULL));
    bst_free(tree);
    printf("ok!\n");
}

void test_bst_predecessor() {
    printf("test_bst_predecessor... ");
    bst *tree = create_test_tree();

    for (size_t i = TEST_TREE_SIZE - 1; i > 0; i--) {
        bst_node *node = bst_find(tree, ordered_keys[i]);
        bst_node *predecessor = bst_predecessor(node);
        bst_node *found_predecessor = bst_find(tree, ordered_keys[i - 1]);
        assert(predecessor == found_predecessor);
    }

    assert(!bst_predecessor(bst_subtree_first(tree->root)));
    assert(!bst_predecessor(NULL));
    bst_free(tree);
    printf("ok!\n");
}

void test_bst_find() {
    printf("test_bst_find... ");
    bst *tree = create_test_tree();
    bst *empty_tree = bst_new();

    for (size_t i = 0; i < TEST_TREE_SIZE; i++) {
        bst_node *found = bst_find(tree, keys[i]);
        assert(found);
        assert(!strcmp(found->entry->key, keys[i]));
    }

    assert(!bst_find(tree, "non_existing_key"));
    assert(!bst_find(empty_tree, "any_key"));
    bst_free(tree);
    bst_free(empty_tree);
    printf("ok!\n");
}

void test_bst_insert() {
    printf("test_bst_insert... ");
    bst *tree = create_test_tree();

    size_t insertions = 3;
    char *keys_to_look_at_for_inserted[] = {"a", "e", "w", "m"};
    char *keys_to_insert[] = {"b", "d", "x", "r"};

    for (size_t i = 0; i < insertions; i++) {
        bst_node *node = bst_find(tree, keys_to_look_at_for_inserted[i]);
        bst_node *inserted = bst_insert(tree, keys_to_insert[i], value);
        assert(!bst_insert(tree, keys_to_insert[i], value));
        assert(inserted->parent == node);

        if (strcmp(keys_to_insert[i], keys_to_look_at_for_inserted[i]) < 0)
            assert(node->left == inserted);
        else
            assert(node->right == inserted);

        assert(!strcmp(inserted->entry->key, keys_to_insert[i]));
        assert(!strcmp(inserted->entry->value, value));
    }

    assert_traversal_order(tree);
    bst_free(tree);
    printf("ok!\n");
}

void test_bst_update() {
    printf("test_bst_update... ");
    bst *tree = create_test_tree();
    bst *empty_tree = bst_new();
    char *updated_value = "updated_value";

    for (size_t i = 0; i < TEST_TREE_SIZE; i++) {
        bst_node *updated = bst_update(tree, keys[i], updated_value);
        bst_node *found = bst_find(tree, keys[i]);
        assert(updated == found);
        assert(!strcmp(updated->entry->value, updated_value));
    }

    assert(!bst_update(tree, "non_existing_key", updated_value));
    assert(!bst_update(empty_tree, "any_key", updated_value));
    bst_free(tree);
    bst_free(empty_tree);
    printf("ok!\n");
}

void test_bst_delete() {
    printf("test_bst_delete... ");
    bst *tree = create_test_tree();

    for (size_t i = 0; i < TEST_TREE_SIZE; i++) {
        bst_delete(tree, keys[i]);
        assert(!bst_find(tree, keys[i]));

        if (i != TEST_TREE_SIZE - 1)
            assert(tree->root);
    }

    assert(!tree->root);
    bst_free(tree);
    printf("ok!\n");
}

int main(int argc, char **argv) {
    test_bst_subtree_first();
    test_bst_subtree_last();
    test_bst_successor();
    test_bst_predecessor();
    test_bst_find();
    test_bst_insert();
    test_bst_update();
    test_bst_delete();
    return 0;
}