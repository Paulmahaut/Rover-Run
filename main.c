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
    printf("3. Quit\n");
    printf("Choose an Option (between 1&3): ");
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
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid Option, Please Try Again.\n");
        }
    } while (choice != 3);
    return 0;
}