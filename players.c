#include <assert.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include "players.h"
#include "graph_extend.h"

static void * load_symbol(void * handle, char * filename, char *symbol_name)
{
  void * symbol = dlsym(handle, symbol_name);
  if (symbol == NULL) {
    printf("Cannot load symbol %s from file %s\n", symbol_name, filename);
    exit(EXIT_FAILURE);
  }
  return symbol;
}

struct player player_load(char * filename)
{
  struct player p;

  p.handle = dlopen(filename, RTLD_LAZY);
  if (p.handle == NULL) {
    printf("Cannot open file: %s, %s\n", filename, dlerror());
    exit(EXIT_FAILURE);
  }

  p.initialize = load_symbol(p.handle, filename, "initialize");
  p.get_player_name = load_symbol(p.handle, filename, "get_player_name");
  p.play = load_symbol(p.handle, filename, "play");
  p.finalize = load_symbol(p.handle, filename, "finalize");

  return p;
}

void player_close(struct player * p)
{
  dlclose(p->handle);
}

void players_load(char * filename[NUM_PLAYERS], struct player p[NUM_PLAYERS])
{
  for (int i=0; i < NUM_PLAYERS; ++i)
    p[i] = player_load(filename[i]);
}

void players_close(struct player p[NUM_PLAYERS])
{
  for (size_t i=0; i<NUM_PLAYERS; ++i)
    player_close(&p[i]);
}

int players_choose_start_player()
{
  assert(NUM_PLAYERS == 2);
  return rand() % 2;
}

int players_get_next_player(int current_player)
{
  return 1 - current_player;
}

void player_initialize(int player_id, struct player p, struct graph_t *graph, enum color_t* colors, struct color_set_t *forbidden_colors){
  p.initialize(player_id , graph, colors, forbidden_colors);
}
void players_initialize(struct player p[NUM_PLAYERS], struct graph_t *graph, enum color_t* colors, struct color_set_t *forbidden_colors){
  for(int i=0;i<NUM_PLAYERS;i++){
    player_initialize(i, p[i], graph_copy(graph), graph_colors_copy(colors, graph->num_vertices), forbidden_colors);
  }
}

void player_free(struct player p){
  p.finalize();
}
void players_free(struct player p[NUM_PLAYERS]){
  for(int i=0;i<NUM_PLAYERS;i++){
    player_free(p[i]);
  }
}
