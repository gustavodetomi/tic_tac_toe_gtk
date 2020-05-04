#ifndef __HEADER
#define __HEADER

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <ctype.h>
#include <stdbool.h>

#define n_fields 9

/*
    Structs
*/

typedef struct Field{
    char value;
    int player;
    bool selected;
    GtkWidget *object;
}Field;

typedef struct Avaliable{
    int fields[n_fields];
    int num_f;
}Avaliable;

/*
    Global Variables
*/

GtkBuilder *builder; 
GtkWidget *window;
GtkWidget *label_result;
GtkWidget *bt_play_again;
GtkWidget *label_score;
int n_rounds;
int n_cpu_wins;
int n_player_wins;
int n_ties;
Field fields[n_fields];

/*
    Util
*/

void print_fields();

int* init_upcoming_field(int id_field);

void init_fields();

void reset_game();

void update_score();

/*
    Game Rules
*/

void computer_round(int level);

void player_round(GtkWidget *object);

bool win(int n1, int n2, int n3, char c);

bool verefy_win(char c);

bool is_end_game();

/*
    Interface manipulation
*/

void disable_all_fields();

/*
    "Artificial intelligence"
*/

// Level
int ia_computer(int level);

// Random 
int randomN();

// Defense and atack
int aux_defense_and_atack(char c);

// Atack
int atack();

// Defense
int defense();

/*
    Strategy proximity
*/

void aux_init_upcoming_filed(int n1, int n2, int n3, int vetor[]);

int* init_upcoming_field(int id_field);

int strategy_proximity();

/*
    Strategy best initial field
*/

int best_init_field();

#endif //__HEADER