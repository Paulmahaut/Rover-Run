#include "map.h"
#include "moves.h"
#include "loc.h"
typedef struct s_treeNode {
    t_move move; // mouvment of the node
    int cost; //
    struct s_treeNode **children; // History of travel
    int num_children; // Number of childs
    t_localisation loc; // Localisation of the robot
    t_map map; // Map
} t_treeNode;

t_treeNode* createNode(t_localisation loc,t_move move, int cost);

void addChild(t_treeNode *parent, t_treeNode *child);

void printTree(t_treeNode *node, int level);
int calculateMoveCost(t_localisation loc, t_move move, t_map map);
//oid freeTree(t_treeNode *node);