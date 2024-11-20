#include <stdio.h>
#include "map.h"
#include "tree.h"
#include "moves.h"
#include "loc.h"

int main() {
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);

    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    /* printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }*/
   /* displayMap(map);
    t_treeNode *testNode = createNode(F_10, _soil_cost[PLAIN]); // Example : Move F_10, cost pour PLAIN
    printf("Node created: Move = %s, Cost = %d\n", getMoveAsString(testNode->move), testNode->cost); */
   // createNode(F_10, 1);

   //second test for creating a node and filling it manually
  /*  t_treeNode *root = createNode(F_10, 0); // Move F_10, cost initial 0

    t_treeNode *child1 = createNode(F_20, 1);
    t_treeNode *child2 = createNode(F_30, 2);

    addChild(root, child1);
    addChild(root, child2);

    t_treeNode *child3 = createNode(T_LEFT, 3);
    t_treeNode *child4 = createNode(T_RIGHT, 4);

    addChild(child1, child3);
    addChild(child2, child4);

    printTree(root, 0);*/

 // Create the root node
    t_treeNode *root = createNode(F_10, 0); // Example: Move F_10, initial cost 0
    root->loc = (t_localisation){0, 0}; // Initial location
    root->map = map; // Assign the map to the root node

    // Add children to the root node
    for (int i = 0; i < 9; i++) {
        t_move move = (t_move)i;
        int move_cost = calculateMoveCost(root->loc, move, map);
        if (move_cost != COST_UNDEF) {
            t_treeNode *child = createNode(move, move_cost);
            addChild(root, child);
        }
    }

    // Print the tree
    printTree(root, 0);

    // Free the tree
    //freeTree(root);

    return 0;

    return 0;
}