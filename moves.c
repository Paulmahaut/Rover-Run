#include "moves.h"
#include "map.h"

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

t_localisation locmove(t_localisation loc, t_move move, t_map map) {
    t_localisation new_loc;
    t_soil start_soil = map.soils[loc.pos.y][loc.pos.x];

    // Adjust movement distance if starting from an Erg soil
    if (start_soil == ERG) {
        switch (move) {
            case F_10:
            case B_10:
                // No movement
                return loc;
            case F_20:
                move = F_10;
                break;
            case F_30:
                move = F_20;
                break;
            default:
                break;
        }
    }

    new_loc = translate(loc, move);

    // Handle turning rules for Erg soil
    if (start_soil == ERG) {
        if (move == T_LEFT || move == T_RIGHT) {
            new_loc.ori = rotate(loc.ori, U_TURN);
        } else {
            new_loc.ori = rotate(loc.ori, move);
        }
    } else {
        new_loc.ori = rotate(loc.ori, move);
    }

    return new_loc;
}

char *getMoveAsString(t_move move) {
    return _moves[move];
}