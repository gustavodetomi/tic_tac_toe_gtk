#include "header.h"

void print_fields(){
    for(int i=0;i<n_fields;i++){
        printf("i=%i value=%c player=%i int=%i\n",i,
            fields[i].value,fields[i].player,fields[i].selected);
    }
}

void init_fields(){
    n_rounds = 0;
    n_player_wins = 0;
    n_cpu_wins = 0;
    n_ties = 0;
    gtk_widget_set_sensitive(bt_play_again, FALSE); 
    for(int i=0;i<n_fields;i++){
        // label is a name button
        char name_object[6] = {"label"};
        // convert int to char
        name_object[5] = i + 48; 
        // reference object
        fields[i].object = GTK_WIDGET(gtk_builder_get_object(builder,name_object)); 
        fields[i].value = '?'; 
        // 0 - computer, 1 - player
        fields[i].player = -1; 
        fields[i].selected = false; 
    }
}

void reset_game(){
    n_rounds = 0;
    gtk_widget_set_sensitive(bt_play_again, FALSE); 
    gtk_label_set_label(GTK_LABEL(label_result), "");
    for(int i=0;i<n_fields;i++){
        gtk_widget_set_sensitive (fields[i].object, true); 
        gtk_button_set_label(GTK_BUTTON(fields[i].object), "?"); 
        fields[i].value = '?'; 
        // 0 - computer, 1 - player
        fields[i].player = -1; 
        fields[i].selected = false; 
    }
}

void update_score(){
    char score_text[256];
    char str_n_wins_cpu[256];
    sprintf(str_n_wins_cpu, "%d\n", n_cpu_wins);
    char str_n_wins_player[256];
    sprintf(str_n_wins_player, "%d\n", n_player_wins);
    char str_n_ties[256];
    sprintf(str_n_ties, "%d\n", n_ties);
    strcpy(score_text, "\n***Scoreboard***\n");
    strcpy(score_text, strcat(score_text,"CPU Wins: "));
    strcpy(score_text, strcat(score_text,str_n_wins_cpu));
    strcpy(score_text, strcat(score_text,"Player Wins: "));
    strcpy(score_text, strcat(score_text,str_n_wins_player));
    strcpy(score_text,strcat(score_text,"Ties: "));
    strcpy(score_text, strcat(score_text,str_n_ties));
    gtk_label_set_label(GTK_LABEL(label_score), score_text);
}