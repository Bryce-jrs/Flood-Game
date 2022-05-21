
#include "graph_update.h"

void recursive_update(struct graph_t  *graph, enum color_t* color_graph, int position,
enum color_t original_color, enum color_t new_color)
{
  if (color_graph[position] == original_color){
      int neighbours[4];
      color_graph[position] = new_color;
      graph_fill_neighbours(graph, position, neighbours);
      for(int i = 0; i<4 && neighbours[i]!=-1; ++i){
        if (color_graph[neighbours[i]] != new_color)
          recursive_update(graph,color_graph, neighbours[i], original_color,new_color);
      }
  }
}

int player_position(struct graph_t * graph, int current_player_id){
  if (current_player_id == 0)
      return 0;
  else
      return graph->num_vertices -1;
}


void update_graph(struct graph_t  * graph, enum color_t* colors, int current_player_id, struct move_t move)
{
  if (move.c != NO_COLOR)
    {
      int position=player_position(graph,current_player_id);
      enum color_t original_color=colors[position];
      recursive_update(graph,colors ,position, original_color, move.c);
    }
}
