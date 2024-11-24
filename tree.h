#ifndef TREE_H
#define TREE_H

#include "map.h"
#include "moves.h"
#include "loc.h"

typedef struct Node {
    int cost;
    struct Node** children;
    int num_children;
    t_localisation loc;
    t_move move;
    struct Node* parent;
} Node;

Node* createNode(int cost, t_localisation loc, t_move move);
void addChild(Node* parent, Node* child);
void printTree(Node* node, int level);
void freeTree(Node* root);
Node* findMinCostLeaf(Node* root);
void getOptimalPath(Node* leaf, t_move* path, int* path_length);
void buildTree(Node* root, int depth, t_map map, int max_depth);

#endif // TREE_H