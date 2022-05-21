#ifndef PLAYERS_H
#define PLAYERS_H

#include <stdlib.h>

#include "color.h"
#include "graph.h"
#include "graph_extend.h"

struct player{
  void * handle;
  char const* (*get_player_name) (void);
  void (*initialize) (size_t id, struct graph_t* graph,
		      enum color_t* colors,
		      struct color_set_t forbidden[NUM_PLAYERS]);
  struct move_t (*play)(struct move_t previous_move);
  void* (*finalize) (void);
};

struct player player_load(char * filename);
void player_close(struct player * p);

void players_load(char * filenames[NUM_PLAYERS], struct player p[NUM_PLAYERS]);
void players_close(struct player p[NUM_PLAYERS]);

int players_choose_start_player();
int players_get_next_player(int current_player);

void player_initialize(int player_id, struct player p, struct graph_t *graph, enum color_t* colors, struct color_set_t *forbidden_colors);
void players_initialize(struct player p[NUM_PLAYERS], struct graph_t *graph, enum color_t* colors, struct color_set_t *forbidden_colors);

void player_free(struct player p);
void players_free(struct player p[NUM_PLAYERS]);

void display_graph(enum color_t* colors, int num_vertices);

#endif // PLAYERS_H
