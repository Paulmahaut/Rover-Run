//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_MOVES_H
#define UNTITLED1_MOVES_H

#include "loc.h"
#include "map.h"
/**
 * @brief Array of strings for the possible moves of the robot
 */
static char _moves[8][8] = {"F 10m", "F 20m", "F 30m", "B 10m", "T left", "T right", "U-turn"};

/**
 * @brief Enum for the possible moves of the robot
 */

typedef enum e_move
{
    F_10, // Forward 10 m
    F_20, // Forward 20 m
    F_30, // Forward 30 m
    B_10, // Backward 10 m
    T_LEFT, // Turn left (+90°)
    T_RIGHT, // Turn right (-90°)
    U_TURN
} t_move;

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param ori : the actual orientation of the robot
 * @param move : the move to do
 * @return the new orientation of the robot
 */
t_orientation rotate(t_orientation, t_move );

/**
 * @brief function to translate the robot according to a move and its actual position
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation translate(t_localisation , t_move);

/**
 * @brief function to get a t_move as a string
 * @param move : the move to convert
 * @return the string corresponding to the move
 */
char *getMoveAsString(t_move move);

/**
 * @brief : Function to calculate the new localisation of MARC after a movement
 * @param loc : The current localisation of MARC
 * @param move : The move to be performed (e.g., forward, turn)
 * @param map : The map structure containing terrain information
 * @return The updated localisation of MARC after applying the move and terrain effects
 */
t_localisation locmove(t_localisation, t_move, t_map);

/**
 * @brief : Function to randomly select a sequence of moves for MARC
 * @param selected_moves : Pointer to an array where the selected moves will be stored
 * @return none
 */
void selectRandomMoves(t_move *selected_moves);
#endif //UNTITLED1_MOVES_H