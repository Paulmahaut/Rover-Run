#include "map.h"
#include "moves.h"
#include "loc.h"
typedef struct s_treeNode {
    t_move move; // mouvement of the node
    int cost; //
    struct s_treeNode **child1; // Children with the mov "F_10"  Forward 10 m
    struct s_treeNode **child2; // Children with the mov "F_20"  Forward 20 m
    struct s_treeNode **child3; // Children with the mov "F_30"  Forward 30 m
    struct s_treeNode **child4; // Children with the mov "B_10"  Backward 10 m
    struct s_treeNode **child5; // Children with the mov "T_LEFT" // Turn left (+90°)
    struct s_treeNode **child6; // Children with the mov "T_RIGHT" // Turn right (-90°)
    struct s_treeNode **child7; // Children with the mov "U_TURN" (180°)
    enum e_move type_mov1; // Variable associated to the mov "F_10"
    enum e_move type_mov2; // Variable associated to the mov "F_20"
    enum e_move type_mov3; // Variable associated to the mov "F_30"
    enum e_move type_mov4; // Variable associated to the mov "B_10"
    enum e_move type_mov5; // Variable associated to the mov "T_LEFT"
    enum e_move type_mov6; // Variable associated to the mov "T_RIGHT"
    enum e_move type_mov7; // Variable associated to the mov "U_TURN"
    t_localisation loc; // Localisation of the robot
    t_map map; // Map
} t_treeNode;

t_treeNode* createNode(t_move move, int cost);

void addChild(t_treeNode *parent, t_treeNode *child);

void printTree(t_treeNode *node, int level);
int calculateMoveCost(t_localisation loc, t_move move, t_map map);
//oid freeTree(t_treeNode *node);