#ifndef UPDATE_H
#define UPDATE_H

#include <stdio.h>
#include <stdlib.h>
#include "graph_extend.h"


void recursive_update(struct graph_t * graph, enum color_t* color_graph, int position, enum color_t original_color, enum color_t new_color);
int player_position(struct graph_t * graph, int curent_player_id);
void update_graph(struct graph_t * graph, enum color_t* color_graph, int current_player_id, struct move_t move);

#endif 
