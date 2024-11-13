

#include "loc.h"
#include "map.h"
#include "moves.h"


typedef struct s_treeNode {
    t_localisation loc;
    int cost;                 // Accumulated cost up to this node
    struct s_treeNode** children; // Array of pointers to children nodes
    int num_children;         // Number of children (max 9 for 9 possible moves)
    int height;              // Height of the node
    int width;              // Width of the node
    int used_moves[100];         // Array of moves used to reach this node
} t_treeNode;