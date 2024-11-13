//
// Created by moust on 10/11/2024.
//

#ifndef ROVER_RUN_TREE_H
#define ROVER_RUN_TREE_H

#include "loc.h"
#include "map.h"
#include "moves.h"

// Tree node representing a state in the movement sequence
typedef struct s_treeNode {
    t_localisation loc;       // Rover's location and orientation
    int cost;                 // Accumulated cost up to this node
    struct s_treeNode** children; // Array of pointers to children nodes
    int num_children;         // Number of children (max 9 for 9 possible moves)
} t_treeNode;

/**
 * @brief Initialize a new tree node with a given location and cost.
 * @param loc The location of the node.
 * @param cost The cost at this node.
 * @return Pointer to the newly created node.
 */
t_treeNode* createNode(t_localisation loc, int cost);

/**
 * @brief Add a child node to a parent node.
 * @param parent The parent node.
 * @param child The child node to add.
 */
void addChild(t_treeNode* parent, t_treeNode* child);

/**
 * @brief Free all nodes in the tree to avoid memory leaks.
 * @param root The root node of the tree.
 */
void freeTree(t_treeNode* root);

/**
 * @brief Find the path with the minimum cost to a leaf node.
 * @param root The root node of the tree.
 * @param min_cost Pointer to store the minimum cost found.
 * @return The sequence of moves leading to the minimum-cost leaf.
 */
int findMinCostPath(t_treeNode* root, int* min_cost);

#endif //ROVER_RUN_TREE_H
