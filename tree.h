
#include "moves.h"

typedef struct s_treeNode {
    t_move move; // mouvment of the node
    int cost; //
    struct s_treeNode **children; // History of travel
    int num_children; // Number of childs
} t_treeNode;

t_treeNode* createNode(t_move move, int cost);

void addChild(t_treeNode *parent, t_treeNode *child);

void printTree(t_treeNode *node, int level);

//oid freeTree(t_treeNode *node);