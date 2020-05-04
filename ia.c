#include "header.h"

/*
    Main IA function and Aux
    level 1 -- random atack
    level 2 -- defend if the player is going to win and random atack
    level 3 -- first defend if the player is going to win
               and win the game if possible
    level 4 -- first verify if the computer win the game 
               after defense and random atack
    level 5 -- Strategy Proximity + level 4
                
*/

int ia_computer(int level){
    printf("proximity=%i\n",strategy_proximity());
    int def;
    int atk;
    if(level > 1){
        def = defense();
        atk = atack();
    }
    if(level == 1){
        return randomN();
    } else if(level == 2){
        if(def == -1){
            return randomN();
        } else {
            return def;
        }
    } else if(level == 3){
        if(def == -1){
            if(atk != -1)
                return atk;
            return randomN();
        } else {
            return def;
        }
    } else if(level == 4){
        if(atk == -1){
            if(def != -1)
                return def;
            return randomN();
        } else {
            return atk;
        }
    } else if(level == 5){
        int strategy_p = strategy_proximity();
        if(atk == -1){
            if(def != -1)
                return def;
            if(strategy_p != -1)
                return strategy_p;
            return randomN();
        } else {
            return atk;
        }
    } else if(level == 6){
        int strategy_p = strategy_proximity();
        int best_initial = best_init_field();
        if(atk == -1){
            if(def != -1)
                return def;
            if(strategy_p != -1)
                return strategy_p;
            if(best_initial != -1)
                return best_initial;
            return randomN();
        } else {
            return atk;
        }
    }
    return -1;
}

Avaliable avaliable_fields(){
    Avaliable v;
    v.num_f=0;
    for(int i=0;i<n_fields;i++){
        if(fields[i].selected == false){
            v.fields[v.num_f] = i;
            v.num_f++;
        }
    }
    return v;
}

/*
    Random
*/

int randomN(){
    int num = -1;
    Avaliable avaliable = avaliable_fields();
    for(int i=0;i<avaliable.num_f;i++){
        srand(time(0) * num);
        num = rand() % avaliable.num_f;
    }
    return avaliable.fields[num];
}

/*
    Skills
*/

// 'X' = defense, 'O' = Atack
int aux_defense_and_atack(char c){
    Avaliable a = avaliable_fields();
    int num_defense = -1;
    for(int i=0; i<a.num_f;i++){
        bool stop = false;
        char aux = fields[a.fields[i]].value;
        fields[a.fields[i]].value = c;
        if(verefy_win(c) == true){
            stop = true;
            num_defense = a.fields[i];
        }
        fields[a.fields[i]].value = aux;
        if(stop)
            return num_defense;
    }
    return num_defense;
}

int defense(){
    return aux_defense_and_atack('X');
}

int atack(){
    return aux_defense_and_atack('O');
}

/*
    Strategy proximity
*/

void aux_init_upcoming_filed(int n1, int n2, int n3, int vetor[]){
    vetor[0] = n1;
    vetor[1] = n2;
    vetor[2] = n3; 
}

int* init_upcoming_field(int id_field){
    int *proximity = malloc(3 * sizeof (int));
    if(id_field == 0)
        aux_init_upcoming_filed(1,3,4,proximity);
    if(id_field == 1)
        aux_init_upcoming_filed(0,4,2,proximity);
    if(id_field == 2)
        aux_init_upcoming_filed(1,4,5,proximity);
    if(id_field == 3)
        aux_init_upcoming_filed(0,6,4,proximity);
    if(id_field == 4)
        aux_init_upcoming_filed(1,3,5,proximity);
    if(id_field == 5)
        aux_init_upcoming_filed(2,4,8,proximity);
    if(id_field == 6)
        aux_init_upcoming_filed(3,4,7,proximity);
    if(id_field == 7)
        aux_init_upcoming_filed(4,6,8,proximity);
    if(id_field == 8)
        aux_init_upcoming_filed(5,7,4,proximity);
    return proximity;
}

int strategy_proximity(){
    for(int i=0; i<n_fields;i++){
        if(fields[i].value == 'O'){
            int *proximity = init_upcoming_field(i);
            for(int j=0; j<3;j++){
                if(fields[proximity[j]].value == '?'){
                    return proximity[j];
                }
            }
        }
    }
    return -1;
}

/*
    Strategy best initial field
*/

int best_init_field(){
    if(fields[4].selected == false)
        return 4;
    int num = -1;
    Avaliable avaliable = avaliable_fields();
    Avaliable avaliable_best;
    avaliable_best.num_f = 0;
    for(int i=0;i<avaliable.num_f;i++){
        if(avaliable.fields[i] == 0 || avaliable.fields[i] == 2 || 
           avaliable.fields[i] == 6 || avaliable.fields[i] == 8){
            avaliable_best.fields[avaliable_best.num_f] = avaliable.fields[i];
            avaliable_best.num_f++;
        }
    }
    if(avaliable_best.num_f == 0)
        return -1;
    for(int i=0;i<avaliable_best.num_f;i++){
        srand(time(0) * num);
        num = rand() % avaliable_best.num_f;
    }
    return avaliable_best.fields[num];
}