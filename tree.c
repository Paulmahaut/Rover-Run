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

void buildTree(Node* root, int depth, t_map map, int max_depth) {
    if (depth >= max_depth) return;
    for (int i = 0; i < 9; i++) { // Iterate over all possible 9 moves from the enum
        t_localisation new_loc = locmove(root->loc, (t_move)i, map);
        if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) { // Check if the move puts MARC in the map or not
            int new_cost = map.costs[new_loc.pos.y][new_loc.pos.x];
            if (new_cost == COST_UNDEF || new_cost >= 10000) {
                continue;
            }
            Node* child = createNode(new_cost, new_loc, (t_move)i); // Create a node for the current move
            addChild(root, child); // Create a child of the newly created node
            buildTree(child, depth + 1, map, max_depth); // Use the child created to make the next part of tree
        }
    }
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
    // Iterate over all children of the current node
    for (int i = 0; i < root->num_children; i++) {
        Node* childMinLeaf = findMinCostLeaf(root->children[i]);

        // If the child has a lower cost than the current minimum then get the new minimum leaf
        if (childMinLeaf && childMinLeaf->cost < minLeaf->cost) {
            minLeaf = childMinLeaf;
        }
    }
    return minLeaf;
}

void getOptimalPath(Node* leaf, t_move* path, int* path_length) {
    *path_length = 0;
    // Traverse from leaf to root, storing the moves to know what MARC will need to do
    while (leaf) {
        path[(*path_length)++] = leaf->move; // Store the move at the current depth
        leaf = leaf->parent;
    }
    // Reverse the path to get the correct order in root to leaf instead of leaf to root like had at first
    for (int i = 0; i < *path_length / 2; i++) {
        t_move temp = path[i];  // Swap elements
        path[i] = path[*path_length - 1 - i];
        path[*path_length - 1 - i] = temp;
    }
}