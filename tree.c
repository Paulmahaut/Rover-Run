
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