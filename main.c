#include "header.h"

int main(int argc, char *argv[]){
    
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    label_result = GTK_WIDGET(gtk_builder_get_object(builder,"label_result"));

    bt_play_again = GTK_WIDGET(gtk_builder_get_object(builder,"bt_play_again"));

    label_score = GTK_WIDGET(gtk_builder_get_object(builder,"label_score"));

    init_fields();
    
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

void on_window_main_destroy(){
    gtk_main_quit();
}

void bt_field_clicked(GtkWidget *object , gpointer data){
    // const char *text = gtk_button_get_label(GTK_BUTTON(object));
    // printf("%s\n",text);
    n_rounds++;
    printf("%i\n",n_rounds);
    player_round(object);
    if(is_end_game())
        return;
    print_fields();
    printf("---------------------\n");
    if(n_rounds < 5){
        computer_round(6);
        if(is_end_game())
            return;
    } else {
        gtk_label_set_label(GTK_LABEL(label_result), "The game tied!");
        disable_all_fields();
        gtk_widget_set_sensitive(bt_play_again, true); 
        n_ties++;
        update_score();
        printf("The game tied!\n");
    }
    print_fields();
    printf("---------------------\n");
}

void bt_play_again_clicked(){
    reset_game();
}