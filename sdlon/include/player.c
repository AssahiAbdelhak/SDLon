#include "player.h"
#include "sdlon_init.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * crée l'inventaire du joueur
 * et le met à 0
*/
inventory player_inventory_create(char * file_name){
    inventory inventaire;
    FILE * file;
    inventaire.path_to_save = malloc(sizeof(char)*MAX_LEN_PATH);
    int i;

    for(i=0;i<NB_ITEMS;i++){
        inventaire.list_item[i] = 0;
    }
    inventaire.max_item_per_slot = MAX_ITEM_PER_SLOT;
    strcpy(inventaire.path_to_save, file_name);

    file = fopen(inventaire.path_to_save, "a");
    fprintf(file, "0 0 0 0 0\n");
    fclose(file);

    return inventaire;
}

player_t player_create(char * name, int genre, char * file_name){

    player_t player;
    int i, init=-1;
    char * path = malloc(sizeof(char)*MAX_LEN_PATH);
    strcpy(path, "data/players_data/player_name_");
    strcat(path, file_name);

    //assignation nom/genre
    player.name = malloc(sizeof(char)*MAX_LEN_NAME);
    strcpy(player.name, name);
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
    fclose(file);

    player.inventaire = player_inventory_create(path);

    //libération mémoire
    free(path);
    return player;
}

player_t player_init(char * file_name){
    player_t player;

    char * path = malloc(sizeof(char)*MAX_LEN_PATH);
    strcpy(path, "data/players_data/player_name_");
    strcat(path, file_name);

    char * name = malloc(sizeof(char)*MAX_LEN_NAME);
    int genre, sdlon_index[6], i, cpt=0, invent_qtt;

    FILE * file;
    file = fopen(path, "r");

    fscanf(file, "%s %d %d %d %d %d %d %d\n", name, &genre, &sdlon_index[0], &sdlon_index[1], &sdlon_index[2], &sdlon_index[3], &sdlon_index[4], &sdlon_index[5]);

    player.name = malloc(sizeof(char)*MAX_LEN_NAME);
    strcpy(player.name, name);
    player.genre = genre;

    for(i=0;i<MAIN_MAX;i++){
        player.sd[i] = sdlon_s[sdlon_index[i]];
        if(sdlon_index[i]!=-1){
            cpt++;
        }
    }
    player.nb_current_sdlon = cpt;

    //initiate inventaire
    player.inventaire.path_to_save = malloc(sizeof(char)*MAX_LEN_PATH);
    strcpy(player.inventaire.path_to_save, path);
    
    i=0;
    while (!feof(file))
    {
        fscanf(file, "%d", &invent_qtt);
        player.inventaire.list_item[i] = invent_qtt;
        i++;
    }
    
    player.inventaire.max_item_per_slot = MAX_ITEM_PER_SLOT;
    
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
    free(player->inventaire.path_to_save);
    player->name=NULL;
    return 0;
}

/**
 * Ajoute un item
 * à l'inventaire du joueurs
 * retourne 0 si réussis
 * 1 si aucun item recevable
 * et le nombre d'item non recevable si une partie est recevable
*/
int add_items(int num_item, int qtt, player_t * player){
    int nb_items = player->inventaire.list_item[num_item];

    if(nb_items >= MAX_ITEM_PER_SLOT){
        return 1;
    }else if((nb_items + qtt) >= MAX_ITEM_PER_SLOT){
        player->inventaire.list_item[num_item] = MAX_ITEM_PER_SLOT;
        return ((nb_items + qtt)-MAX_ITEM_PER_SLOT); //retourne le nombre d'objet non recevable
    }else{
        player->inventaire.list_item[num_item] += qtt;
    }
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

/**
 * fonction de sauvegarde des donnée
 * des datas du joueurs
 * box/set/items
*/
int save_player_data(char * file_name){

}