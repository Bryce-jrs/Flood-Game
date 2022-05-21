#ifndef STRATEGY_H
#define STRATEGY_H


#include "check_validity.h"
#include "graph_update.h"

enum color_t * authorizedColor(struct color_set_t forbidden[],
int forbidden_nb,int current_player_id, int nb_color);
int choiceMove(struct graph_t * g,enum color_t * colors, int current_player_id, 
struct color_set_t forbidden[],int forbidden_nb,int nb_color);

#endif 