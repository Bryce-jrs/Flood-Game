#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include "players.h"
#include "graph_update.h"

// Fonctions pour manipuler component
int is_in(int x,int tab[]);
void add(int x, int tab[]);
int size_of_area(int area[]);

void graph_component(struct graph_t  * g, enum color_t  * colors, int vertex, int component[]);

// Fonctions de test

int is_adjacent_color(struct graph_t  * g, enum color_t  * colors, enum color_t color, int component[]);

int is_touching_opponent_area(struct graph_t  * g, int component[], int opponent_component[]);

int is_color_forbidden(enum color_t color,struct color_set_t forbidden[],int player_id,int forbidden_nb);


//Fonction de vérification

int is_move_valid(struct graph_t  * g, enum color_t  * colors, struct color_set_t forbidden[],
int forbidden_nb, struct move_t move, int current_player_id);


#endif // CHECK_H
