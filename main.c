#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "tree.h"
#include "moves.h"
#include "loc.h"

#define NUM_MOVES 9

// Function to randomly select 9 moves based on their availability
void selectRandomMoves(t_move *selected_moves) {
    int availability[7] = {22, 15, 7, 7, 21, 21, 7};
    for (int i = 0; i < NUM_MOVES; i++) {
        int move;
        do {
            move = rand() % 7;
        } while (availability[move] == 0);
        selected_moves[i] = (t_move)move;
        availability[move]--;
    }
}

int main() {
    srand(time(NULL)); // Initialize random seed

    t_map map;
    t_localisation marc_loc = loc_init(0, 5, NORTH);

#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
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

        for (int i = 0; i < NUM_MOVES; i++) {
            t_localisation best_loc = marc_loc;
            int min_cost = COST_UNDEF;
            t_move best_move = selected_moves[i];

            for (int j = 0; j < NUM_MOVES; j++) {
                t_localisation new_loc = move(marc_loc, selected_moves[j]);
                if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) {
                    int cost = map.costs[new_loc.pos.y][new_loc.pos.x];
                    if (cost < min_cost) {
                        min_cost = cost;
                        best_move = selected_moves[j];
                        best_loc = new_loc;
                    }
                }
            }

            marc_loc = best_loc;
            printf("Move: %s\n", getMoveAsString(best_move));
            printf("Robot position: (%d, %d), Orientation: %s\n", marc_loc.pos.x, marc_loc.pos.y,
                   (marc_loc.ori == NORTH) ? "NORTH" : (marc_loc.ori == EAST) ? "EAST" : (marc_loc.ori == SOUTH) ? "SOUTH" : "WEST");

            if (map.soils[marc_loc.pos.y][marc_loc.pos.x] == BASE_STATION) {
                printf("Robot has reached the base station.\n");
                break;
            }
        }
    }

    printCostMap(map);
    return 0;
}