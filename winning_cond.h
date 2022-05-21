#ifndef VICTORY_H
#define VICTORY_H

#include <stdlib.h>
#include "check_validity.h"

int sum(int tab[], int taille);
int winningByFault(struct graph_t  * g,enum color_t  * colors,struct color_set_t forbidden[],
int forbidden_nb,struct move_t move, int current_player_id);
int winningByPassTurn(int passTurn[]);
int is_winning(struct graph_t  * g,enum color_t  * colors,struct color_set_t forbidden[],
int forbidden_nb,struct move_t move, int current_player_id, int passTurn[]);
int whoHasTheMost(struct graph_t  * g,enum color_t  * colors);
int whoWon(struct graph_t  * g,enum color_t  * colors,struct color_set_t forbidden[],
int forbidden_nb,struct move_t move,int current_player_id);
#endif 