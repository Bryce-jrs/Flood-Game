#include "player.h"
#include "players.h"
#include "graph_extend.h"
#include "graph_update.h"
#include "check_validity.h"
#include <string.h>

struct player_t {
  struct graph_t *g;
  enum color_t *c;
  int player_id;
  struct color_set_t forbidden_colors;
};

struct player_t p;

char const* get_player_name()
{
  return "Maro\t";
}



int coverage(){
  int component[p.g->num_vertices +1];
  component[0]=-1;
  int position = player_position(p.g, p.player_id);
  graph_component(p.g, p.c, position,component);
  return size_of_area(component);
}

int cov(int r){
  struct graph_t* g_copy = graph_copy(p.g);
  enum color_t * c_copy = graph_colors_copy(p.c, p.g->num_vertices);

  int cov_before = coverage();
  struct move_t m = {.c = r};
  update_graph(g_copy, c_copy, p.player_id, m);
  int cov_after = coverage();

  graph_free(g_copy);
  graph_free_colors(c_copy);

  return cov_after <= cov_before;
}

int opponent_ter(int r){
  struct graph_t* g_copy = graph_copy(p.g);
  enum color_t * c_copy = graph_colors_copy(p.c, p.g->num_vertices);

  struct move_t m = {.c = r};
  update_graph(g_copy, c_copy, p.player_id, m);

  int current_player_component[g_copy->num_vertices +1];
  current_player_component[0]=-1;
  int other_player_component[g_copy->num_vertices +1];
  other_player_component[0]=-1;
  graph_component(g_copy, c_copy, p.g->positions[p.player_id],current_player_component);
  graph_component(g_copy, c_copy, 1 - p.player_id,other_player_component);
  int ret = is_touching_opponent_area(g_copy, current_player_component,other_player_component);

  graph_free(g_copy);
  graph_free_colors(c_copy);
  return ret;
}

int generate_random_valid_color(){
  int r = rand()%(MAX_COLOR-1);
  for(int i = 0; i< MAX_COLOR && p.forbidden_colors.t[i] != -1 ; i++){
    if ( r == atoi(&(p.forbidden_colors.t[i])) || p.c[p.g->positions[p.player_id]] == r || cov(r) || opponent_ter(r))
    {
      generate_random_valid_color(p.forbidden_colors);
    }
  }
  return r;
}

void initialize(size_t id, struct graph_t* graph,
                enum color_t* colors,
                struct color_set_t forbidden[NUM_PLAYERS]){
  p.g = graph;
  p.c = colors;
  p.player_id = id;
  p.forbidden_colors = forbidden[id];
}



struct move_t play(struct move_t previous_move)
{
  printf("PLAYING AS player");
  update_graph(p.g, p.c, 1-p.player_id, previous_move);
  struct move_t move = {.c = generate_random_valid_color() };
  printf("I played the color %d\n",move.c);
  update_graph(p.g, p.c, p.player_id, move);
  return move;
}


void finalize(){
  graph_free(p.g);
  graph_free_colors(p.c);
}
