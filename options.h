#ifndef _FLOOD_OPTIONS_H_
#define _FLOOD_OPTIONS_H_

#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "graph_extend.h"


struct options_t {
  enum graph_type_t shape;
  enum color_type_t color_algo;
  int width;
  int color_nb;
  int forbidden_nb;
  char* player_names[NUM_PLAYERS];
};


void parse_options(int argc, char* argv[], struct options_t *options);

#endif // _FLOOD_OPTIONS_H_
