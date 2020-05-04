#include "header.h"

void computer_round(int level){
    int n_field = ia_computer(level);
    printf("IA=%i\n",n_field);
    gtk_button_set_label(GTK_BUTTON(fields[n_field].object), "O"); 
    gtk_widget_set_sensitive (fields[n_field].object, FALSE); 
    fields[n_field].value = 'O';
    fields[n_field].player = 0;
    fields[n_field].selected = true;
}

void player_round(GtkWidget *object){
    gtk_button_set_label(GTK_BUTTON(object), "X"); 
    gtk_widget_set_sensitive (object, FALSE);
    for(int i=0;i<n_fields;i++){
        if(fields[i].object == object){
            fields[i].value = 'X';
            fields[i].player = 1;
            fields[i].selected = true;
        }
    }
}

bool win(int n1, int n2, int n3, char c){
    if(fields[n1].value == c && fields[n2].value == c && fields[n3].value == c)
        return true;
    return false;
}

bool verefy_win(char c){
    // line
    if(win(0,1,2,c) == true || win(3,4,5,c) == true || win(6,7,8,c)==true)
        return true;
    // colun
    if(win(0,3,6,c) == true || win(1,4,7,c) == true || win(2,5,8,c)==true)
        return true;
    // diagonal
    if(win(6,4,2,c) == true || win(0,4,8,c) == true)
        return true;
    return false;
} 


bool is_end_game(){
    if(verefy_win('X')){
        gtk_label_set_label(GTK_LABEL(label_result), "You win!");
        disable_all_fields();
        gtk_widget_set_sensitive(bt_play_again, true); 
        n_player_wins++;
        update_score();
        printf("The player win!\n");
        return true;
    } else if(verefy_win('O')){
        gtk_label_set_label(GTK_LABEL(label_result), "You louse! The computer win!");
        disable_all_fields();
        gtk_widget_set_sensitive(bt_play_again, true); 
        n_cpu_wins++;
        update_score();
        printf("You louse! The computer win!\n");
        return true;
    }
    return false;
}
