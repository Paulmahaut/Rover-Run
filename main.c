// main.c
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "tree.h"
#include "moves.h"
#include "loc.h"

int main() {
    t_map map;
    t_localisation marc_loc = loc_init(0, 0, NORTH); // Initial position of MARC

#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);

    Node* root = createNode(map.costs[marc_loc.pos.y][marc_loc.pos.x], marc_loc, F_10);

    // Build the tree (example for 2 levels)
    for (int i = 0; i < 9; i++) {
        t_move move1 = (t_move)i;
        t_localisation loc1 = move(marc_loc, move1);
        int cost1 = map.costs[loc1.pos.y][loc1.pos.x];
        Node* child1 = createNode(cost1, loc1, move1);
        addChild(root, child1);

        for (int j = 0; j < 8; j++) {
            t_move move2 = (t_move)j;
            t_localisation loc2 = move(loc1, move2);
            int cost2 = map.costs[loc2.pos.y][loc2.pos.x];
            Node* child2 = createNode(cost2, loc2, move2);
            addChild(child1, child2);
        }
    }

    // Find the optimal path
    Node* minLeaf = findMinCostLeaf(root);
    t_move path[5];
    int path_length;
    getOptimalPath(minLeaf, path, &path_length);

    printf("Optimal path:\n");
    for (int i = 0; i < path_length; i++) {
        printf("%s\n", getMoveAsString(path[i]));
    }

    freeTree(root);













    //---------------------------------------------------------------------------------------------------------------------
 /*   Node* root = (Node*)malloc(sizeof(Node));
    root->cost = 10;
    root->num_children = 2;
    root->children = (Node**)malloc(root->num_children * sizeof(Node*));

    Node* child1 = (Node*)malloc(sizeof(Node));
    child1->cost = 20;
    child1->num_children = 0;
    child1->children = NULL;

    Node* child2 = (Node*)malloc(sizeof(Node));
    child2->cost = 15;
    child2->num_children = 0;
    child2->children = NULL;

    root->children[0] = child1;
    root->children[1] = child2;

// Afficher l'arbre
    printf("Arbre :\n");
    print_tree(root, 0);*/
    return 0;
}



