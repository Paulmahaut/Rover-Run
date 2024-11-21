#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Node* createNode(int cost, t_localisation loc, t_move move) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->cost = cost;
    node->loc = loc;
    node->move = move;
    node->children = NULL;
    node->num_children = 0;
    node->parent = NULL;
    return node;
}

void addChild(Node* parent, Node* child) {
    parent->children = (Node**)realloc(parent->children, (parent->num_children + 1) * sizeof(Node*));
    if (parent->children == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    parent->children[parent->num_children] = child;
    parent->num_children++;
    child->parent = parent;
}

void printTree(Node* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("Move: %s, Cost: %d\n", getMoveAsString(node->move), node->cost);
    for (int i = 0; i < node->num_children; i++) {
        printTree(node->children[i], level + 1);
    }
}

void freeTree(Node* root) {
    if (!root) return;
    for (int i = 0; i < root->num_children; i++) {
        freeTree(root->children[i]);
    }
    free(root->children);
    free(root);
}

Node* findMinCostLeaf(Node* root) {
    if (!root) return NULL;
    Node* minLeaf = root;
    for (int i = 0; i < root->num_children; i++) {
        Node* childMinLeaf = findMinCostLeaf(root->children[i]);
        if (childMinLeaf && childMinLeaf->cost < minLeaf->cost) {
            minLeaf = childMinLeaf;
        }
    }
    return minLeaf;
}

void getOptimalPath(Node* leaf, t_move* path, int* path_length) {
    *path_length = 0;
    while (leaf) {
        path[(*path_length)++] = leaf->move;
        leaf = leaf->parent;
    }
    for (int i = 0; i < *path_length / 2; i++) {
        t_move temp = path[i];
        path[i] = path[*path_length - 1 - i];
        path[*path_length - 1 - i] = temp;
    }
}