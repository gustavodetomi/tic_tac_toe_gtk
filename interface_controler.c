#include "header.h"

void disable_all_fields(){
    for(int i=0;i<n_fields;i++)
        gtk_widget_set_sensitive (fields[i].object, FALSE); 
}