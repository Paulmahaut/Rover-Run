// tree.h
#ifndef TREE_H
#define TREE_H

#include "map.h"
#include "moves.h"
#include "loc.h"

typedef struct Node {
    int cost;               // Cost of the node
    struct Node** children; // Array of pointers to child nodes
    int num_children;       // Number of children
    t_localisation loc;     // Localisation of the robot
    t_move move;            // Move made to reach this node
            parent;                 // Parent node
} Node;

Node* createNode(int cost, t_localisation loc, t_move move);
void addChild(Node* parent, Node* child);
void printTree(Node* node, int level);
void freeTree(Node* root);
Node* findMinCostLeaf(Node* root);
void getOptimalPath(Node* leaf, t_move* path, int* path_length);

#endif // TREE_H