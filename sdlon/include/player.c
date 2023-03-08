#include "player.h"
#include "sdlon_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

player_t player_create(char * name, int genre){
    player_t player;
    int i;
    player.name = name;
    player.genre = genre;
    player.nb_current_sdlon = 0;
    for(i=0;i<MAIN_MAX;i++){
        strcpy(player.sd[i].nom, sdlon_s[-1].nom);
    }
    return player;
}

player_t player_init(char * name_file){
    player_t player;
    FILE * file = NULL;

    char * name;
    int genre, sdlon_index[6], i, cpt=0;

    file = fopen(name_file, "r");

    fscanf(file, "%s %d %d %d %d %d %d %d\n", name, &genre, 
    &sdlon_index[0], &sdlon_index[1], &sdlon_index[2], &sdlon_index[3], &sdlon_index[4], &sdlon_index[5]);
    
    player.name = name;
    player.genre = genre;

    for(i=0;i<MAIN_MAX;i++){
        player.sd[i] = sdlon_s[sdlon_index[i]];
        if(sdlon_index[i]!=-1){
            cpt++;
        }
    }
    player.nb_current_sdlon = cpt;
    printf("%s", player.sd[1].nom);
    return player;
}