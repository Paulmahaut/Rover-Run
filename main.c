#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "tree.h"
#include "moves.h"
#include "loc.h"

#define NUM_MOVES 9
#define PHASE_MOVES 5


void DisplayMenu() {
    printf("Menu:\n");
    printf("1. 1st map of dim 10x10\n");
    printf("2. 2nd map of dim 8x8\n");
    printf("3. Your map (you have to change the path of your in the code\n");
    printf("4. Calculate the complexity\n");
    printf("5. Quit\n");
    printf("Choose an Option (between 1&5): ");
}

int main() {
    int choice;
    do {
        DisplayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("You choose 1st map\n");
                srand(time(NULL)); // Initialize random seed
                t_map map1;
                t_localisation marc_loc1 = loc_init(8, 5, NORTH);

#if defined(_WIN32) || defined(_WIN64)
                map1 = createMapFromFile("..\\maps\\example1.map");
#else
                map1 = createMapFromFile("../maps/example1.map");
#endif
                printf("Map created with dimensions %d x %d\n", map1.y_max, map1.x_max);
                printCostMap(map1);

                while (map1.soils[marc_loc1.pos.y][marc_loc1.pos.x] != BASE_STATION) {
                    t_move selected_moves[NUM_MOVES];
                    selectRandomMoves(selected_moves);

                    printf("Selected moves:\n");
                    for (int i = 0; i < NUM_MOVES; i++) {
                        printf("%s\n", getMoveAsString(selected_moves[i]));
                    }

                    int phase_moves = PHASE_MOVES;
                    int move_counts[7] = {0}; // Array to keep track of move counts

                    for (int i = 0; i < phase_moves; i++) {
                        t_localisation best_loc = marc_loc1;
                        int min_cost = COST_UNDEF;
                        t_move best_move = selected_moves[i];

                        for (int j = 0; j < NUM_MOVES; j++) {
                            if (move_counts[selected_moves[j]] < 1) { // Check if the move can still be executed
                                t_localisation new_loc = locmove(marc_loc1, selected_moves[j], map1);
                                if (isValidLocalisation(new_loc.pos, map1.x_max, map1.y_max)) {
                                    int cost = map1.costs[new_loc.pos.y][new_loc.pos.x];
                                    if (cost < min_cost) {
                                        min_cost = cost;
                                        best_move = selected_moves[j];
                                        best_loc = new_loc;
                                    }
                                }
                            }
                        }

                        marc_loc1 = best_loc;
                        move_counts[best_move]++; // Increment the move count
                        printf("Move: %s\n", getMoveAsString(best_move));
                        printf("Robot position: (%d, %d), Orientation: %s\n", marc_loc1.pos.x, marc_loc1.pos.y,
                               (marc_loc1.ori == NORTH) ? "NORTH" : (marc_loc1.ori == EAST) ? "EAST" : (marc_loc1.ori == SOUTH) ? "SOUTH" : "WEST");

                        if (map1.soils[marc_loc1.pos.y][marc_loc1.pos.x] == BASE_STATION) {
                            printf("Robot has reached the base station.\n");
                            break;
                        }

                        // Reduce phase moves if ending on a Reg soil
                        if (map1.soils[marc_loc1.pos.y][marc_loc1.pos.x] == REG) {
                            phase_moves = 4;
                        }
                        if (map1.soils[marc_loc1.pos.y][marc_loc1.pos.x] == CREVASSE) {
                            printf("YOU ARE DEAD !");
                        }
                    }
                }

                printCostMap(map1);
                return 0;
            case 2:
                printf("You choose the 2nd map\n");
                srand(time(NULL)); // Initialize random seed

                t_map map2;
                t_localisation marc_loc2 = loc_init(1, 5, NORTH);

#if defined(_WIN32) || defined(_WIN64)
                map2 = createMapFromFile("..\\maps\\example2.map");
#else
                map2 = createMapFromFile("../maps/example2.map");
#endif
                printf("Map created with dimensions %d x %d\n", map2.y_max, map2.x_max);
                printCostMap(map2);

                while (map2.soils[marc_loc2.pos.y][marc_loc2.pos.x] != BASE_STATION) {
                    t_move selected_moves[NUM_MOVES];
                    selectRandomMoves(selected_moves);

                    printf("Selected moves:\n");
                    for (int i = 0; i < NUM_MOVES; i++) {
                        printf("%s\n", getMoveAsString(selected_moves[i]));
                    }

                    int phase_moves = PHASE_MOVES;
                    int move_counts[7] = {0}; // Array to keep track of move counts

                    for (int i = 0; i < phase_moves; i++) {
                        t_localisation best_loc = marc_loc2;
                        int min_cost = COST_UNDEF;
                        t_move best_move = selected_moves[i];

                        for (int j = 0; j < NUM_MOVES; j++) {
                            if (move_counts[selected_moves[j]] < 1) { // Check if the move can still be executed
                                t_localisation new_loc = locmove(marc_loc2, selected_moves[j], map2);
                                if (isValidLocalisation(new_loc.pos, map2.x_max, map2.y_max)) {
                                    int cost = map2.costs[new_loc.pos.y][new_loc.pos.x];
                                    if (cost < min_cost) {
                                        min_cost = cost;
                                        best_move = selected_moves[j];
                                        best_loc = new_loc;
                                    }
                                }
                            }
                        }

                        marc_loc2 = best_loc;
                        move_counts[best_move]++; // Increment the move count
                        printf("Move: %s\n", getMoveAsString(best_move));
                        printf("Robot position: (%d, %d), Orientation: %s\n", marc_loc2.pos.x, marc_loc2.pos.y,
                               (marc_loc2.ori == NORTH) ? "NORTH" : (marc_loc2.ori == EAST) ? "EAST" : (marc_loc2.ori == SOUTH) ? "SOUTH" : "WEST");

                        if (map2.soils[marc_loc2.pos.y][marc_loc2.pos.x] == BASE_STATION) {
                            printf("Robot has reached the base station.\n");
                            break;
                        }

                        // Reduce phase moves if ending on a Reg soil
                        if (map2.soils[marc_loc2.pos.y][marc_loc2.pos.x] == REG) {
                            phase_moves = 4;
                        }
                        if (map2.soils[marc_loc2.pos.y][marc_loc2.pos.x] == CREVASSE) {
                            printf("YOU ARE DEAD !");
                        }
                    }
                }

                printCostMap(map2);
                return 0;
            case 3:
                srand(time(NULL)); // Initialize random seed
                t_map map;
                t_localisation marc_loc = loc_init(1, 1, NORTH); // CHANGE THE START OF THE ROVER

#if defined(_WIN32) || defined(_WIN64)
                map = createMapFromFile("PUT THE PATH L.172"); // CHANGE THE PATH OF YOUR MAP HERE
#else
                map = createMapFromFile("PUT THE PATH L.174"); // CHANGE THE PATH OF YOUR MAP HERE
#endif
                printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
                printCostMap(map);

                while (map.soils[marc_loc.pos.y][marc_loc.pos.x] != BASE_STATION) {
                    t_move selected_moves[NUM_MOVES];
                    selectRandomMoves(selected_moves);

                    printf("Selected moves:\n");
                    for (int i = 0; i < NUM_MOVES; i++) {
                        printf("%s\n", getMoveAsString(selected_moves[i]));
                    }

                    int phase_moves = PHASE_MOVES;
                    int move_counts[7] = {0}; // Array to keep track of move counts

                    for (int i = 0; i < phase_moves; i++) {
                        t_localisation best_loc = marc_loc;
                        int min_cost = COST_UNDEF;
                        t_move best_move = selected_moves[i];

                        for (int j = 0; j < NUM_MOVES; j++) {
                            if (move_counts[selected_moves[j]] < 1) { // Check if the move can still be executed
                                t_localisation new_loc = locmove(marc_loc, selected_moves[j], map);
                                if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) {
                                    int cost = map.costs[new_loc.pos.y][new_loc.pos.x];
                                    if (cost < min_cost) {
                                        min_cost = cost;
                                        best_move = selected_moves[j];
                                        best_loc = new_loc;
                                    }
                                }
                            }
                        }

                        marc_loc = best_loc;
                        move_counts[best_move]++; // Increment the move count
                        printf("Move: %s\n", getMoveAsString(best_move));
                        printf("Robot position: (%d, %d), Orientation: %s\n", marc_loc.pos.x, marc_loc.pos.y,
                               (marc_loc.ori == NORTH) ? "NORTH" : (marc_loc.ori == EAST) ? "EAST" : (marc_loc.ori == SOUTH) ? "SOUTH" : "WEST");

                        if (map.soils[marc_loc.pos.y][marc_loc.pos.x] == BASE_STATION) {
                            printf("Robot has reached the base station.\n");
                            break;
                        }

                        // Reduce phase moves if ending on a Reg soil
                        if (map.soils[marc_loc.pos.y][marc_loc.pos.x] == REG) {
                            phase_moves = 4;
                        }
                        if (map.soils[marc_loc.pos.y][marc_loc.pos.x] == CREVASSE) {
                            printf("YOU ARE DEAD !");
                        }
                    }
                }

                printCostMap(map);
                return 0;
            case 4:
                printf("You chose to calculate the complexity\n");
                srand(time(NULL)); // Initialize random seed
                t_map map3;
                t_localisation marc_loc3 = loc_init(8, 5, NORTH);

#if defined(_WIN32) || defined(_WIN64)
                map3 = createMapFromFile("PUT THE PATH L.240"); // CHANGE THE PATH OF YOUR MAP HERE
#else
                map3 = createMapFromFile("PUT THE PATH L.242"); // CHANGE THE PATH OF YOUR MAP HERE
#endif
                printf("Map created with dimensions %d x %d\n", map3.y_max, map3.x_max);
                clock_t start, end;

                // Complexity of the Tree construction phase
                start = clock();
                Node* root = createNode(map3.costs[marc_loc3.pos.y][marc_loc3.pos.x], marc_loc3, F_10);
                buildTree(root, 0, map3, PHASE_MOVES);
                end = clock();
                printf("Tree construction time: %.2f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
                printf("Time complexity: O(9^n)\n"); // It creates the tree of n depth with the 9 possible moves,
                                                     // so if we chose 5 moves, it will be 9^5

                // Complexity of the Leaf search phase
                start = clock();
                Node* minLeaf = findMinCostLeaf(root);
                end = clock();
                printf("Leaf search time: %.2f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
                printf("Time complexity: O(9^n)\n"); //It's this much because findMinCostLeaf goes through all the nodes of the tree of depth n that has 9 moves

                // Complexity of the Path calculation phase
                start = clock();
                t_move path[PHASE_MOVES];
                int path_length;
                getOptimalPath(minLeaf, path, &path_length);
                end = clock();
                printf("Path calculation time: %.2f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
                printf("Time complexity: O(n)\n"); // Since you go across the only path that is correct, you do it once so it's n complexity

                // Guiding MARC phase
                start = clock();
                t_localisation marc_loc4 = marc_loc3;
                for (int i = 0; i < path_length; i++) {
                    marc_loc4 = locmove(marc_loc4, path[i], map3);
                    if (map3.soils[marc_loc4.pos.y][marc_loc4.pos.x] == BASE_STATION) {
                        printf("Robot reached base station.\n");
                        break;
                    }
                }
                end = clock();
                printf("Complete guidance time: %.2f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
                printf("Time complexity: O(n)\n"); // Since MARC follows the optimal path, it also goes only once so it's n complexity

                return 0;
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid Option, Please Try Again.\n");
        }
    } while (choice != 5);
    return 0;
}