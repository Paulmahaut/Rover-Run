#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "loc.h"
#include "moves.h"
#include "tree.h"
int main() {
    t_map map;
    t_localisation marc_loc = loc_init(0, 0, NORTH); // Initial position of MARC

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    //displayMapWithPosition(map, marc_loc);
    // Move MARC forward 10m
    marc_loc = move(marc_loc, F_10);
    // Move MARC forward 20m
    marc_loc = move(marc_loc, F_20);
    //displayMapWithPosition(map, marc_loc);
    //move Marc to the right
    marc_loc = move(marc_loc, T_RIGHT);
    displayMapWithPosition(map, marc_loc);
    return 0;

    // Création d'un arbre simple pour tester
    Node* root = (Node*)malloc(sizeof(Node));
    root->cost = 10;
    root->num_children = 2;
    root->children = (Node**)malloc(root->num_children * sizeof(Node*));

    Node* child1 = (Node*)malloc(sizeof(Node));
    child1->cost = 20;
    child1->num_children = 0;
    child1->children = NULL;

    Node* child2 = (Node*)malloc(sizeof(Node));
    child2->cost = 15;
    child2->num_children = 0;
    child2->children = NULL;

    root->children[0] = child1;
    root->children[1] = child2;

    // Afficher l'arbre
    printf("Arbre :\n");
    print_tree(root, 0);

}