#include "graph_extend.h"

struct graph_t *graph_init(int width, enum graph_type_t shape) {
  struct graph_t *g = malloc(sizeof(*g));
  g->num_vertices = width*width;
  g->t = empty_matrix(g->num_vertices, g->num_vertices);
  g->positions[0] = 0;
  g->positions[1] = g->num_vertices - 1;

  switch (shape) {
    case SQUARE:
      graph_build_square(g);
      break;
    default:
      graph_build_square(g);
      break;
  }

  return g;
}

void graph_build_square(struct graph_t *g) {
  size_t num_vertices = g->num_vertices;
  size_t root = floor(sqrt(num_vertices));

  for(size_t i = 0; i < num_vertices; i++) {
    if ((i%root != 0) && (i >= 1)){
      matrix_add_edge(g->t, i, i-1);
      matrix_add_edge(g->t, i-1, i);
    }

    if (i >= root){
      matrix_add_edge(g->t, i, i-root);
      matrix_add_edge(g->t, i-root, i);
    }
  }
}

enum color_t *random_coloration(struct graph_t *g, int color_nb) {
  int count = g->num_vertices;
  enum color_t *graph_color = malloc(sizeof(*graph_color) * count);


  for (int i = 0; i < count; ++i){
    graph_color[i] = generate_rand(color_nb);
  }

  return graph_color;
}

enum color_t *graph_init_colors(struct graph_t *g, int color_nb, enum graph_type_t graph_type) {
  enum color_t *colors = NULL;

  switch(graph_type) {
    case RANDOM:
        colors = random_coloration(g, color_nb);
      break;
    default:
        colors = random_coloration(g, color_nb);
      break;
  }

  return colors;
}

void graph_forbidden_init_colors(struct color_set_t *forbidden, int nb_player, int forbidden_nb) {
  struct color_set_t forbidden_graph;
  int k = 0;
  char color = 0;
  int j = 0;

  if(forbidden_nb == 0){
    for (int i = 0; i < nb_player; ++i) {
      for (j = 0; j < MAX_COLOR; ++j) {
        forbidden[i].t[j] = NO_COLOR;
      }
    }
  }

  else{
    for (int i = 0; i < nb_player; ++i) {
      for (j = 0; j < forbidden_nb; ++j) {
        k = j-1;
        color = generate_rand(MAX_COLOR);

        while (color == forbidden_graph.t[k] && k >= 0) {
	         --k;
	         color = generate_rand(MAX_COLOR);
        }

        forbidden_graph.t[j] = color;
      }

      if (forbidden_nb < MAX_COLOR) {
        forbidden_graph.t[j] = NO_COLOR;
      }
      forbidden[i] = forbidden_graph;
    }
  }
}

struct graph_t *graph_copy(struct graph_t* g) {
  struct graph_t *g_copy = malloc(sizeof(*g_copy));
  g_copy->num_vertices = g->num_vertices;
  g_copy->positions[0] = g->positions[0];
  g_copy->positions[1] = g->positions[1];
  g_copy->t = empty_matrix(g->num_vertices, g->num_vertices);
  gsl_spmatrix_uint_memcpy(g_copy->t, g->t);
  return g_copy;
}

enum color_t *graph_colors_copy(enum color_t* colors, int num_vertices) {
  enum color_t *g_copy = malloc(sizeof(*g_copy)*num_vertices);
  for(int i = 0; i<num_vertices; i++){
    g_copy[i] = colors[i];
  }
  return g_copy;
}


void graph_fill_neighbours(struct graph_t *g, size_t position, int *neighbours) {
  matrix_fill_neighbours(g->t, position, neighbours);
}

void graph_free(struct graph_t *g) {
  matrix_free(g->t);
  free(g);
}

void graph_free_colors(enum color_t *graph_color) {
  free(graph_color);
}

void display_graph(enum color_t* colors, int num_vertices) {
  int line = floor(sqrt(num_vertices));

  for (int i = 0; i < num_vertices; i++) {
    if(i%line == 0)
      printf("\n");
    switch(colors[i]){
    case 0:
      printf(ANSI_COLOR_BLUE    "  "    ANSI_COLOR_RESET);
      break;
    case 1:
      printf(ANSI_COLOR_RED     "  "     ANSI_COLOR_RESET);
      break;
    case 2:
      printf(ANSI_COLOR_GREEN   "  "   ANSI_COLOR_RESET);
      break;
    case 3:
      printf(ANSI_COLOR_YELLOW  "  "  ANSI_COLOR_RESET);
      break;
    case 4:
      printf(ANSI_COLOR_ORANGE    "  "    ANSI_COLOR_RESET);
      break;
    case 5:
      printf(ANSI_COLOR_MAGENTA "  " ANSI_COLOR_RESET);
      break;
    case 6:
      printf(ANSI_COLOR_CYAN    "  "    ANSI_COLOR_RESET);
      break;
    case 7:
      printf(ANSI_COLOR_PINK   "  "    ANSI_COLOR_RESET);
      break;
    default:
      break;
    }
  }
  printf("\n");
}
