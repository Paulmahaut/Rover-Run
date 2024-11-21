#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "tree.h"
#include "moves.h"
#include "loc.h"

void printMapWithRobot(t_map map, t_localisation loc) {
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            if (i == loc.pos.y && j == loc.pos.x) {
                printf("R ");
            } else {
                switch (map.soils[i][j]) {
                    case BASE_STATION: printf("B "); break;
                    case PLAIN: printf(". "); break;
                    case ERG: printf("~ "); break;
                    case REG: printf("^ "); break;
                    case CREVASSE: printf("C "); break;
                    default: printf("? "); break;
                }
            }
        }
        printf("\n");
    }
    printf("Robot position: (%d, %d), Orientation: %s\n", loc.pos.x, loc.pos.y,
           (loc.ori == NORTH) ? "NORTH" : (loc.ori == EAST) ? "EAST" : (loc.ori == SOUTH) ? "SOUTH" : "WEST");
}

void printCostMap(t_map map) {
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            if (map.costs[i][j] == COST_UNDEF) {
                printf("## ");
            } else {
                printf("%2d ", map.costs[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    t_map map;
    t_localisation marc_loc = loc_init(0, 0, NORTH);

#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    printMapWithRobot(map, marc_loc);
    printCostMap(map);

    Node* root = createNode(map.costs[marc_loc.pos.y][marc_loc.pos.x], marc_loc, F_10);

    for (int i = 0; i < 9; i++) {
        t_move move1 = (t_move)i;
        t_localisation loc1 = move(marc_loc, move1);
        if (loc1.pos.x < 0 || loc1.pos.x >= map.x_max || loc1.pos.y < 0 || loc1.pos.y >= map.y_max) continue;
        int cost1 = map.costs[loc1.pos.y][loc1.pos.x];
        Node* child1 = createNode(cost1, loc1, move1);
        addChild(root, child1);

        for (int j = 0; j < 8; j++) {
            t_move move2 = (t_move)j;
            t_localisation loc2 = move(loc1, move2);
            if (loc2.pos.x < 0 || loc2.pos.x >= map.x_max || loc2.pos.y < 0 || loc2.pos.y >= map.y_max) continue;
            int cost2 = map.costs[loc2.pos.y][loc2.pos.x];
            Node* child2 = createNode(cost2, loc2, move2);
            addChild(child1, child2);
        }
    }

    Node* minLeaf = findMinCostLeaf(root);
    t_move path[5];
    int path_length;
    getOptimalPath(minLeaf, path, &path_length);

    printf("Optimal path:\n");
    for (int i = 0; i < path_length; i++) {
        printf("%s\n", getMoveAsString(path[i]));
        marc_loc = move(marc_loc, path[i]);
        printMapWithRobot(map, marc_loc);
        printCostMap(map);
    }

    freeTree(root);
    return 0;
}