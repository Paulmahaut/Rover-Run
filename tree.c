//
// Created by moust on 10/11/2024.
//

#include "tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "tree.h"

// Create a new tree node with a specified location and cost
t_treeNode* createNode(t_localisation loc, int cost) {
    t_treeNode* node = (t_treeNode*)malloc(sizeof(t_treeNode));
    node->loc = loc;
    node->cost = cost;
    node->children = (t_treeNode**)malloc(9 * sizeof(t_treeNode*)); // 9 max possible moves
    node->num_children = 0;
    return node;
}

// Add a child to a parent node
void addChild(t_treeNode* parent, t_treeNode* child) {
    if (parent->num_children < 9) {
        parent->children[parent->num_children] = child;
        parent->num_children++;
    } else {
        fprintf(stderr, "Error: Cannot add more children to this node.\n");
    }
}

// Recursively free all nodes in the tree
void freeTree(t_treeNode* root) {
    if (root == NULL) return;
    for (int i = 0; i < root->num_children; i++) {
        freeTree(root->children[i]);
    }
    free(root->children);
    free(root);
}

// Helper function to recursively find the minimum-cost path
void findMinCostPathHelper(t_treeNode* node, int* min_cost, int* result_cost) {
    if (node == NULL) return;

    // Leaf node check
    if (node->num_children == 0) {
        if (node->cost < *min_cost) {
            *min_cost = node->cost;
            *result_cost = node->cost;
        }
        return;
    }

    // Traverse each child to find the minimum-cost path
    for (int i = 0; i < node->num_children; i++) {
        findMinCostPathHelper(node->children[i], min_cost, result_cost);
    }
}

// Find the minimum cost path starting from the root
int findMinCostPath(t_treeNode* root, int* min_cost) {
    *min_cost = INT_MAX;
    int result_cost = 0;
    findMinCostPathHelper(root, min_cost, &result_cost);
    return result_cost;
}