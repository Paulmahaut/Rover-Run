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
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    // Set initial position of MARC
    t_localisation marc_loc = loc_init(0, 0, NORTH);

    // Create the root of the movement tree with initial cost
    t_treeNode* root = createNode(marc_loc, map.costs[marc_loc.pos.y][marc_loc.pos.x]);

    // Find the optimal path in terms of cost from root to leaf
    int min_cost;
    findMinCostPath(root, &min_cost);
    printf("Minimum cost to reach target: %d\n", min_cost);

    // Free allocated resources for the tree
    freeTree(root);

    return 0;
}