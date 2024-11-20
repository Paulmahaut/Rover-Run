#include "map.h"
#include "moves.h"
#include "loc.h"
typedef struct s_treeNode {
    t_move move; // mouvement of the node
    int cost; //
    struct s_treeNode **children1; // History of travel
    struct s_treeNode **children2; // History of travel
    struct s_treeNode **children3; // History of travel
    struct s_treeNode **children4; // History of travel
    struct s_treeNode **children5; // History of travel
    struct s_treeNode **children6; // History of travel
    struct s_treeNode **children7; // History of traveL
    enum e_move type_mov1; enum e_move F_10;
    int type_mov2;
    int type_mov3;
    int type_mov4;
    int type_mov5;
    int type_mov6;
    int type_mov7;
    t_localisation loc; // Localisation of the robot
    t_map map; // Map
} t_treeNode;

t_treeNode* createNode(t_move move, int cost);

void addChild(t_treeNode *parent, t_treeNode *child);

void printTree(t_treeNode *node, int level);
int calculateMoveCost(t_localisation loc, t_move move, t_map map);
//oid freeTree(t_treeNode *node);