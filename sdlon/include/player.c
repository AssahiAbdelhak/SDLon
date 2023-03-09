#include "player.h"
#include "sdlon_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

player_t player_create(char * name, int genre, char * file_name){

    player_t player;
    int i, init=-1;
    char * path = malloc(sizeof(char)*80);
    strcpy(path, "data/players_data/player_name_");
    strcat(path, file_name);

    //assignation nom/genre
    player.name = name;
    player.genre = genre;

    //mise à 0 des sdlons
    player.nb_current_sdlon = 0;
    for(i=0;i<MAIN_MAX;i++){
        strcpy(player.sd[i].nom, sdlon_s[-1].nom);
    }

    //creation du fichier de sauvegarde des données du joueur
    FILE * file;
    file = fopen(path, "w");
    fprintf(file, "%s %d %d %d %d %d %d %d\n", name, genre, init, init, init, init, init, init);

    //libération mémoire
    fclose(file);
    free(path);
    return player;
}

player_t player_init(char * file_name){
    player_t player;

    char * path = malloc(sizeof(char)*80);
    strcpy(path, "data/players_data/player_name_");
    strcat(path, file_name);

    char * name = malloc(sizeof(char)*80);
    int genre, sdlon_index[6], i, cpt=0;

    FILE * file;
    file = fopen(path, "r");

    fscanf(file, "%s %d %d %d %d %d %d %d\n", name, &genre, &sdlon_index[0], &sdlon_index[1], &sdlon_index[2], &sdlon_index[3], &sdlon_index[4], &sdlon_index[5]);
    
    player.name = malloc(sizeof(char)*80);
    strcpy(player.name, name);
    player.genre = genre;

    for(i=0;i<MAIN_MAX;i++){
        player.sd[i] = sdlon_s[sdlon_index[i]];
        if(sdlon_index[i]!=-1){
            cpt++;
        }
    }
    player.nb_current_sdlon = cpt;
    printf("%s", player.sd[1].nom);
    fclose(file);
    free(path);
    free(name);
    return player;
}

int player_quit(player_t * player){
    if(player==NULL){
        return 1;
    }
    free(player->name);
    player->name=NULL;
    return 0;
}

/**
 * initialise les items d'un joueur
 * au chargement d'un jeu
*/
int item_init(){
    return 0;
}

/**
 * Ajoute un item
 * à l'inventaire du joueurs
*/
int add_items(){
    return 0;
}

/**
 * retire un item
 * à l'inventaire du joueur
*/
int remove_items(){
    return 0;
}

/**
 * utilise un item dans l'inventaire du joueur
*/
int use_item(){
    return 0;
}

/**
 * Fonction qui ajoute un sdlon
 * dans la main courante d'un joueurs
*/
int add_sdlon_in_set(sdlon sd){
    return 0;
}

/**
 * Fonction qui retire un sdlon
 * de la main courante d'un joueurs
*/
int remove_sdlon_in_set(sdlon sd){
    return 0;
}

/**
 * Fonction qui switch
 * les sdlons du set du joueur
*/
int switch_sdlon_from_set(sdlon sd){
    remove_sdlon_in_set(sd);
    add_sdlon_in_set(sd);
    return 0;
}

/**
 * Fonction qui envoie un sdlon dans une boite
 * pour capturer des sdlons
 * sans les avoir dans sa main
*/
int send_sdlon_in_box(sdlon sd){
    return 0;
}

/**
 * Fonction qui charge les sdlons 
 * dans la boite de stockage
*/
int load_box(char * name){
    return 0;
}

/**
 * créé une boite
 * dans laquel le joueur
 * pourras stocker ses sdlons
*/
int create_box(){
    return 0;
}