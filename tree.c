#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

t_treeNode* createNode(t_move move, int cost) {
    t_treeNode *node = malloc(sizeof(t_treeNode));
    node->move = move;
    node->cost = cost;
    node->children = NULL;
    node->num_children = 0;
    return node;
}

void addChild(t_treeNode *parent, t_treeNode *child) {
    parent->children = realloc(parent->children, (parent->num_children + 1) * sizeof(t_treeNode *));
    parent->children[parent->num_children] = child;
    parent->num_children++;
}

void printTree(t_treeNode *node, int level) {
    if (!node) return;

    // knowing the level of the node
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    // node information
    printf("Move: %s, Cost: %d\n", getMoveAsString(node->move), node->cost);

    // recursive call for children
    for (int i = 0; i < node->num_children; i++) {
        printTree(node->children[i], level + 1);
    }
}


/*void freeTree(t_treeNode *root) {
    if (!root) return;
    for (int i = 0; i < root->num_children; i++) {
        freeTree(root->children[i]);
    }
    free(root->children);
    free(root);
}*/

