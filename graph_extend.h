#ifndef _FLOOD_GRAPH_EXTEND_H_
#define _FLOOD_GRAPH_EXTEND_H_

#include "graph.h"
#include "matrix.h"
#include "random_generator.h"
#include <stdio.h>

#define ANSI_COLOR_RED     "\033[0;41m"
#define ANSI_COLOR_GREEN   "\033[0;42m"
#define ANSI_COLOR_YELLOW  "\033[0;43m"
#define ANSI_COLOR_BLUE    "\033[0;44m"
#define ANSI_COLOR_MAGENTA "\033[0;45m"
#define ANSI_COLOR_CYAN    "\033[0;46m"
#define ANSI_COLOR_ORANGE  "\033[48:2:255:165:0m"
#define ANSI_COLOR_PINK "\033[48;2;255;87;197m"
#define ANSI_COLOR_RESET   "\033[0m"

enum color_type_t { RANDOM=0 };

struct graph_t *graph_init(int width, enum graph_type_t shape);

void graph_build_square(struct graph_t *g);

enum color_t *graph_init_colors(struct graph_t *g, int color_nb, enum graph_type_t graph_type);

void graph_forbidden_init_colors(struct color_set_t *forbidden, int nb_player, int forbidden_nb);

struct graph_t *graph_copy(struct graph_t* g);

void graph_fill_neighbours(struct graph_t *g, size_t position, int *neighbours);

void graph_free(struct graph_t *g);

void graph_free_colors(enum color_t *graph_color);

enum color_t *graph_colors_copy(enum color_t* colors, int num_vertices);

void display_graph(enum color_t* colors, int num_vertices);

#endif // _FLOOD_GRAPH_EXTEND_H_
