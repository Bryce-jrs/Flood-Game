#include "winning_cond.h"


// Sum element of a array

int sum(int tab[], int taille){
    int sum = 0;
    int i =0;
    for(i=0; i<taille; ++i)
        sum+= tab[i];
    return sum;
}

// returns the boolean true (1) if the player have played a wrong move

int winningByFault(struct graph_t  * g,enum color_t  * colors,struct color_set_t forbidden[],
int forbidden_nb,struct move_t move, int current_player_id){
    return !is_move_valid(g,colors,forbidden,forbidden_nb,move,current_player_id);
}

// Check if the players have played NO_COLOR
// take as parameter a array of boolean passTurn
// The boolean are initialised at false
// If the player p has played NO_COLOR the boolean is changed to true.

int winningByPassTurn(int passTurn[]){
    return sum(passTurn,NUM_PLAYERS)!=0 && sum(passTurn,NUM_PLAYERS)%2==0;
}


// return true if the game is finished in other word if a player have won according to the rules

int is_winning(struct  graph_t  * g,enum color_t  * colors,struct color_set_t forbidden[],
int forbidden_nb,struct move_t move, int current_player_id, int passTurn[]){
    return winningByFault(g,colors,forbidden,forbidden_nb,move,current_player_id)|| winningByPassTurn(passTurn);
}

// calculates the area of each player and return the id player whith the more greater area
// if the victory happened by passTurn else if the victory happened by fault return the id of the other player

int whoHasTheMost(struct graph_t  * g,enum color_t  * colors){
    int area[2]={0};
    for(int i= 0; i<NUM_PLAYERS; ++i){
        int component[g->num_vertices +1];
        component[0]=-1;
        int position = player_position(g,i);
        graph_component(g,colors,position,component);
        area[i] = size_of_area(component);
    }
    if (area[0]>area[1])
        return 0;
    else if (area[0]<area[1])
        return 1;
    else
        return -1;
}

int whoWon(struct graph_t  * g,enum color_t  * colors,struct color_set_t forbidden[],
int forbidden_nb,struct move_t move,int current_player_id){
    if ( winningByFault(g,colors,forbidden,forbidden_nb,move,current_player_id))
        return 1-current_player_id;
    else{
        int winner = whoHasTheMost(g,colors);
        return winner;
    }
}
