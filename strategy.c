#include "strategy.h" 


// filter the array colors to the colors which are colors from av valid move 

enum color_t * authorizedColor(struct color_set_t forbidden[],
int forbidden_nb,int current_player_id, int nb_color){

    enum color_t *rightColor = malloc(sizeof(*rightColor) * MAX_COLOR);
    int nb_elt = 0;
    
    for(int i =0; i<nb_color;++i){
        for (int j = 0; j < forbidden_nb; ++j) {
            if (forbidden[current_player_id].t[j] != i){
                rightColor[nb_elt]= i;
                nb_elt+=1;
            }
        }
    }
    rightColor[MAX_COLOR-1]= nb_elt;
    return rightColor;
}


// choice as color the color which enables to conquer a maximum of area 

int choiceMove(struct graph_t * g,enum color_t * colors, int current_player_id, 
struct color_set_t forbidden[],int forbidden_nb,int nb_color){

    int maxArea = 0;
    int choix =0;
    enum color_t *rightColor = authorizedColor(forbidden,forbidden_nb,current_player_id,nb_color);
    int nb_elt = rightColor[MAX_COLOR-1];

    if(nb_elt==0){
        free(rightColor);
        return NO_COLOR;
    }
    else{
        for(int i =0; i<nb_elt;++i){
            int connexe[]={-1};
            struct graph_t *copy = graph_copy(g);
            enum color_t *c=graph_colors_copy(colors,copy->num_vertices);
            int position = player_position(copy,current_player_id);
            struct move_t move ={.c=rightColor[i]};
            update_graph(copy,c,current_player_id,move);
            graph_component(copy,c,position,connexe);
            graph_free(copy);
            free(c);
            
            if (size_of_area(connexe)>maxArea){
                maxArea=size_of_area(connexe);
                choix = rightColor[i];
            }
        }
        free(rightColor);
        return choix;
    }
}




