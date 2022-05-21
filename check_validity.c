#include "check_validity.h"

int is_in(int x,int tab[])
{
  int i=0;
  while (tab[i]!=-1)
    {
      if (x==tab[i]) return 1;
      ++i;
    }
  return 0;
}

void add(int x, int tab[])
{
  int i=0;
  while (tab[i]!=-1)
    {
      ++i;
    }
  tab[i]=x;
  tab[i+1]=-1;
}

int size_of_area(int area[])
{
  int i=0;
  while (area[i]!=-1)
    {
      ++i;
    }
  return i;
}


void graph_component(struct graph_t  * g, enum color_t  * colors, int vertex, int component[])
{
  add(vertex,component);
  int neighbours[4];
  graph_fill_neighbours(g, vertex, neighbours);
  int i=0;
  for(i=0; i<4 && neighbours[i]!= -1; ++i)
    {
      if ( (colors[vertex] == colors[neighbours[i]]) &&
	   (!is_in(neighbours[i],component)) )
	{
	  graph_component(g,colors,neighbours[i],component);
	}

    }
}


//Returns 1 if the color is adjacent, 0 if it's not

int is_adjacent_color(struct graph_t  * g, enum color_t  * colors, enum color_t color, int component[])
{
  int i=0;
  int neighbours[4];
  while(component[i]!=-1)
    {
      graph_fill_neighbours(g,component[i], neighbours);
      for(int j=0; j<4 &&(neighbours[j]!= -1); ++j)
	{
	  if (colors[neighbours[j]] == color)
	    {
	      return 1;
	    }
	}
      ++i;
    }
  return 0;
}




int is_touching_opponent_area(struct graph_t  * g, int component[], int opponent_component[])
{
  int i=0;
  int neighbours[4];
  while(component[i]!=-1)
    {
      graph_fill_neighbours(g,component[i], neighbours);
      for(int j=0; j<4 &&(neighbours[j]!= -1); ++j)
	{
	  if (is_in(neighbours[j],opponent_component))
	    {
	      return 1;
	    }
	}
      ++i;
    }
  return 0;
}


int is_color_forbidden(enum color_t color,struct color_set_t forbidden[],int player_id, int forbidden_nb)
{
  for(int i=0; i < forbidden_nb &&forbidden[player_id].t[i] !=-1; ++i){
    if (forbidden[player_id].t[i]==color)
      return 1;
  }
  return 0;
}



int is_move_valid(struct graph_t  * g, enum color_t  * colors, struct color_set_t forbidden[],
int forbidden_nb, struct move_t move, int current_player_id)
{
  int current_player_position=player_position(g, current_player_id);
  int other_player_position=player_position(g,players_get_next_player(current_player_id));
  int current_player_component[g->num_vertices +1];
  current_player_component[0]=-1;
  int other_player_component[g->num_vertices +1];
  other_player_component[0]=-1;

  if (is_color_forbidden(move.c,forbidden, current_player_id,forbidden_nb)){
    return 0;
  }

  graph_component(g,colors, current_player_position,current_player_component);
  graph_component(g,colors, other_player_position,other_player_component);
  if (move.c == colors[other_player_position] &&
    is_touching_opponent_area(g, current_player_component,other_player_component)){
    return 0;
  }
  return 1;
}
