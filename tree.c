#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
/*                    ICI
t_treeNode* createNode(t_move move, int cost) {
    t_treeNode *node = malloc(sizeof(t_treeNode));
    node->move = move;
    node->cost = cost;
    node->children = NULL;
    node->num_children = 0;
    return node;
}

// Première version de la fonction addChild
void addChild(t_treeNode *parent, t_treeNode *child) {
    parent->children = realloc(parent->children, (parent->num_children + 1) * sizeof(t_treeNode *));
    parent->children[parent->num_children] = child;
    parent->num_children++;
}*/
/*                  ICI
// Deuxième version de la fonction addChild
void addChild(t_treeNode *parent, t_treeNode *child) {
    parent->children = realloc(parent->children, (parent->num_children + 1) * sizeof(t_treeNode *));
    parent->children[parent->num_children] = child;
    parent->num_children++;

    t_localisation loc = parent->loc; // Déclaration de loc
    t_map map = parent->map; // Déclaration de map

    for (int j = 0; j < 9; j++) { // 9 mouvements possibles
        t_move move = (t_move) j;
        int move_cost = calculateMoveCost(loc, move, map);

        if (move_cost == COST_UNDEF) continue; // Ignore les mouvements invalides

        int total_cost = parent->cost + move_cost;

        t_treeNode *child = createNode(move, total_cost);
        addChild(parent, child);

        // Simule la position de MARC après le mouvement pour générer les prochains niveaux
        loc = displacement(loc, move);
    }
}

void printTree(t_treeNode *node, int level) {
    if (!node) return;

    // knowing the level of the node
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    // node information
    printf("Move: %s, Cost: %d\n", getMoveAsString(node->move), node->cost);

    // recursive call for children
    for (int i = 0; i < node->num_children; i++) {
        printTree(node->children[i], level + 1);
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

void freeTree(t_treeNode *root) {
    if (!root) return;
    for (int i = 0; i < root->num_children; i++) {
        freeTree(root->children[i]);
    }
    free(root->children);
    free(root);
}*/
//---------------------------------------------------------------------------------------------------------------------
// tree.c
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Node* createNode(int cost, t_localisation loc, t_move move) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->cost = cost;
    node->loc = loc;
    node->move = move;
    node->children = NULL;
    node->num_children = 0;
    return node;
}

void addChild(Node* parent, Node* child) {
    parent->children = (Node**)realloc(parent->children, (parent->num_children + 1) * sizeof(Node*));
    parent->children[parent->num_children] = child;
    parent->num_children++;
}

void printTree(Node* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("Move: %s, Cost: %d\n", getMoveAsString(node->move), node->cost);
    for (int i = 0; i < node->num_children; i++) {
        printTree(node->children[i], level + 1);
    }
}

void freeTree(Node* root) {
    if (!root) return;
    for (int i = 0; i < root->num_children; i++) {
        freeTree(root->children[i]);
    }
    free(root->children);
    free(root);
}

Node* findMinCostLeaf(Node* root) {
    if (!root) return NULL;
    Node* minLeaf = root;
    for (int i = 0; i < root->num_children; i++) {
        Node* childMinLeaf = findMinCostLeaf(root->children[i]);
        if (childMinLeaf && childMinLeaf->cost < minLeaf->cost) {
            minLeaf = childMinLeaf;
        }
    }
    return minLeaf;
}

void getOptimalPath(Node* leaf, t_move* path, int* path_length) {
    *path_length = 0;
    while (leaf) {
        path[(*path_length)++] = leaf->move;
        leaf = leaf->parent;
    }
    // Reverse the path to get the correct order
    for (int i = 0; i < *path_length / 2; i++) {
        t_move temp = path[i];
        path[i] = path[*path_length - 1 - i];
        path[*path_length - 1 - i] = temp;
    }
}