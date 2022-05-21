#include "player.h"
#include "players.h"
#include "graph_extend.h"
#include <stdlib.h>
#include "graph_update.h"
#include <time.h>
#include "random_generator.h"

struct graph_t *g = NULL;
enum color_t *c= NULL;
size_t id_player=0;
struct color_set_t forbiddens[NUM_PLAYERS];

char const* get_player_name()
{
  return "Sophie\t";
}


void initialize(size_t id, struct graph_t* graph,
                enum color_t* colors,
                struct color_set_t forbidden[NUM_PLAYERS])
{
  g= graph;
  c= colors;
  printf(" %p %p", c,colors);
  id_player=id;
  for(int i=0;i<NUM_PLAYERS;++i){
    forbiddens[i]=forbidden[i];
  }
}

struct move_t play(struct move_t previous_move)
{
  printf("forbidden\n");
  for(int i =0; i<2; ++i)
    printf("%d\n",forbiddens[id_player].t[i]);
  int tab[9]={0,1,2,3,4,5,6,7,-1};
  update_graph(g, c,1-id_player, previous_move);
  int n = generate_rand(9);
  struct move_t move = {.c=tab[n]};
  update_graph(g, c,id_player, move);
  return move;
}


void finalize(){
  graph_free(g);
  graph_free_colors(c);
}
