#include "moves.h"
#include "map.h"
#include <stdlib.h>


#define NUM_MOVES 9

t_orientation rotate(t_orientation ori, t_move move) {
    int rst;
    switch (move) {
        case T_LEFT:
            rst = 3;
            break;
        case T_RIGHT:
            rst = 1;
            break;
        case U_TURN:
            rst = 2;
            break;
        default:
            rst = 0;
            break;
    }
    return (ori + rst) % 4;
}

t_localisation translate(t_localisation loc, t_move move) {
    t_position res = loc.pos;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return loc_init(res.x, res.y, loc.ori);
}

// Function to update the robot's position based on its current location and move
t_localisation locmove(t_localisation loc, t_move move, t_map map) {
    t_localisation new_loc;
    t_soil start_soil = map.soils[loc.pos.y][loc.pos.x];  // Get the soil type of the current location of MARC
    // Adjust movement distance if we are starting from an Erg soil
    if (start_soil == ERG) {
        switch (move) {
            case F_10:
            case B_10:
                // No movement on Erg soil for these moves because it reduces by 10m the movement
                return loc;
            case F_20:
                move = F_10;  // Convert 20m forward to 10m forward
                break;
            case F_30:
                move = F_20;  // Convert 30m forward to 20m forward
                break;
            default:
                break;
        }
    }

    new_loc = translate(loc, move);

    // Handle turning rules for Erg soil since turning is modified in Erg
    if (start_soil == ERG) {
        if (move == T_LEFT || move == T_RIGHT) {
            new_loc.ori = rotate(loc.ori, U_TURN);  // Turn around 180° if turning in Erg
        } else {
            new_loc.ori = rotate(loc.ori, move);  // Regular rotation for other moves
        }
    } else {
        // Regular rotation for other types of terrain
        new_loc.ori = rotate(loc.ori, move);
    }
    return new_loc;
}

char *getMoveAsString(t_move move) {
    return _moves[move];
}


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