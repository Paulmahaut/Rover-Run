#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

t_treeNode* createNode(t_localisation loc, t_move move, int cost) {
    t_treeNode *node = malloc(sizeof(t_treeNode));
    node->loc = loc;
    node->move = move;
    node->cost = cost;
    node->children = NULL;
    node->num_children = 0;
    return node;
}

// Première version de la fonction addChild
/*void addChild(t_treeNode *parent, t_treeNode *child) {
    parent->children = realloc(parent->children, (parent->num_children + 1) * sizeof(t_treeNode *));
    parent->children[parent->num_children] = child;
    parent->num_children++;
}*/

// Deuxième version de la fonction addChild
void addChild(t_treeNode *parent, t_treeNode *child) {
    parent->children = realloc(parent->children, (parent->num_children + 1) * sizeof(t_treeNode *));
    parent->children[parent->num_children] = child;
    parent->num_children++;

    t_localisation new_loc = parent->loc; // Déclaration de loc
    t_map map = parent->map; // Déclaration de map

    for (int j = 0; j < 7; j++) { // 7 mouvements possibles
        t_move move = (t_move) j;
        int move_cost = calculateMoveCost(new_loc, move, map);

        if (move_cost == COST_UNDEF) continue; // Ignore les mouvements invalides

        int total_cost = parent->cost + move_cost;

        t_treeNode *child = createNode(new_loc,move,total_cost);
        addChild(parent, child);

        // Simule la position de MARC après le mouvement pour générer les prochains niveaux
        new_loc = displacement(new_loc, move);
    }
}

void printTree(t_treeNode *node, int level) {
    if (!node) return;

    // knowing the level of the node
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    // Current node's information
    printf("Level %d | Move: %s | Cost: %d | Position: (%d, %d) | Orientation: %d\n",
           level, //C'est le niveau de pronfondeur du node dans le tree, de 0(root) à 7(le dernier move possible)
           getMoveAsString(node->move),
           node->cost,
           node->loc.pos.x,
           node->loc.pos.y,
           node->loc.ori);
    // recursive call for children
    for (int i = 0; i < node->num_children; i++) {
        printTree(node->children[i], level + 1);
    }
}

void generateTree(t_treeNode *parent, t_map map, int depth) {
    if (depth == 0) return; // Ca arrete le tree quand il atteint le depth maximum
    for (int i=0; i<7; i++) {
        // Chaque movement va etre assigne a un case qui va etre dans un child node
        t_move move = (t_move)i;
        t_localisation new_loc = displacement(parent->loc, move);
        if (!isValidLocalisation(new_loc.pos, map.x_max, map.y_max) == map.soils[new_loc.pos.y][new_loc.pos.x] == CREVASSE) {
            continue; // Cette ligne regarde si la nouvelle position de MARC est hors de la map ou dans un crevasse
        }
        int move_cost = _soil_cost[map.soils[new_loc.pos.y][new_loc.pos.x]];
        int total_cost = parent->cost + move_cost;
        t_treeNode *child = createNode(new_loc,move,total_cost);
        addChild(parent,child);
        generateTree(child,map,depth-1);
    }
}

int calculateMoveCost(t_localisation loc, t_move move, t_map map) {
    // Simuler la nouvelle localisation après le mouvement
    t_localisation new_loc = displacement(loc, move);

    // Vérifier si la nouvelle position est valide
    if (!isValidLocalisation(new_loc.pos, map.x_max, map.y_max) ||
        map.soils[new_loc.pos.y][new_loc.pos.x] == CREVASSE) {
        return COST_UNDEF; // Mouvement invalide
    }

    // Retourner le coût du sol correspondant
    return _soil_cost[map.soils[new_loc.pos.y][new_loc.pos.x]];
}

/*void freeTree(t_treeNode *root) {
    if (!root) return;
    for (int i = 0; i < root->num_children; i++) {
        freeTree(root->children[i]);
    }
    free(root->children);
    free(root);
}*/