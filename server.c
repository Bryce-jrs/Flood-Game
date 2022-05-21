#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

#include "color.h"
#include "options.h"
#include "player.h"
#include "players.h"
#include "winning_cond.h"
#include "graph_extend.h"
#include "graph_update.h"

int main(int argc, char *argv[])
{
  srand(time(NULL));
  struct options_t options;

  parse_options(argc, argv, &options);

  struct player players[NUM_PLAYERS];
  players_load(options.player_names, players);

  size_t start_player_id = players_choose_start_player();
  size_t p = start_player_id;
  struct move_t move={NO_COLOR};

  struct color_set_t *forbidden_colors = malloc(sizeof(*forbidden_colors)*NUM_PLAYERS);

  struct graph_t *graph = graph_init(options.width, options.shape);
  enum color_t  *graph_colors = graph_init_colors(graph, options.color_nb, options.color_nb);
  graph_forbidden_init_colors(forbidden_colors, NUM_PLAYERS, options.forbidden_nb);
  players_initialize(players,graph, graph_colors, forbidden_colors);


  int passTurn[NUM_PLAYERS]={0};
  printf("starting graph : \n");
  display_graph(graph_colors, options.width*options.width);

  int n = 0;

  while (1){
    printf("Player %ld is playing\n", p);
    move = players[p].play(move);
    n++;
    printf("Player %ld played the color %d\n",p,move.c);
    if(move.c==NO_COLOR){
      passTurn[p]=1;
    }
    if(!is_move_valid(graph, graph_colors, forbidden_colors, options.forbidden_nb, move, p)){
      printf("player %ld is the winner\n",1-p);
      printf("Game ended after %d turns\n",n);
      break;
    }
    update_graph(graph, graph_colors,p, move);
    display_graph(graph_colors, options.width*options.width);
    if (is_winning(graph,graph_colors,forbidden_colors,options.forbidden_nb,move,p,passTurn)){
      int winner = whoWon(graph,graph_colors,forbidden_colors,options.forbidden_nb,move,p);
      if(winner==-1)
        printf(" Partie nulle");
      else
        printf("Game ended after %d turns The winner is : %s\n",n, players[winner].get_player_name());
      break;
    }

    p = players_get_next_player(p);
  }

  // Cleaning data.
  players_free(players);
  free(forbidden_colors);
  graph_free(graph);
  graph_free_colors(graph_colors);
  players_close(players);
  return 0;
}
