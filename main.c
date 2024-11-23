#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "tree.h"
#include "moves.h"
#include "loc.h"



int main() {
    t_map map;
    t_localisation marc_loc = loc_init(0, 0, NORTH);

    // Load the map from the file
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);

    t_localisation marc_loc = loc_init(0, 0, NORTH); // Initialize MARC's position and orientation

    // Find the base station location and print initial state
    t_position base_position = getBaseStationPosition(map);
    printMapWithRobot(map, marc_loc);

    // Create a tree for optimal pathfinding
    Node *root = createNode(0, marc_loc, F_10); // Cost starts at 0, and initial move is a placeholder
    for (int i = 0; i < 7; i++) { // 7 possible moves
        t_localisation new_loc = move(marc_loc, (t_move)i);
        if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) {
            int cost = _soil_cost[map.soils[new_loc.pos.y][new_loc.pos.x]];
            Node *child = createNode(cost, new_loc, (t_move)i);
            addChild(root, child);
        }
    }

    // Find the minimum-cost path
    Node *optimal_leaf = findMinCostLeaf(root);
    t_move path[5]; // Array to hold the optimal path
    int path_length = 0;
    getOptimalPath(optimal_leaf, path, &path_length);

    // Execute 5 moves from the optimal path
    printf("\nExecuting 5 optimal moves:\n");
    for (int i = 0; i < 5 && i < path_length; i++) {
        marc_loc = move(marc_loc, path[i]);
        printf("Move %d: %s\n", i + 1, getMoveAsString(path[i]));
        printMapWithRobot(map, marc_loc);

        // Stop if MARC reaches the base station
        if (marc_loc.pos.x == base_position.x && marc_loc.pos.y == base_position.y) {
            printf("MARC has reached the base station!\n");
            break;
        }
    }

    // Clean up
    freeTree(root);
    return 0;
}
