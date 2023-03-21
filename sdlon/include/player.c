#include "player.h"
#include "sdlon_init.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Primitives_Box.h"
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
    int i, init=-1, x=0, y=0;
    char * path = malloc(sizeof(char)*MAX_LEN_PATH);
    strcpy(path, "include/data/players_data/player_name_");
    strcat(path, file_name);

    //assignation nom/genre/position
    player.name = malloc(sizeof(char)*MAX_LEN_NAME);
    strcpy(player.name, name);
    player.genre = genre;
    player.x = x;
    player.y = y;

    //mise à 0 des sdlons
    player.nb_current_sdlon = 0;
    for(i=0;i<MAIN_MAX;i++){
        strcpy(player.sd[i].nom, sdlon_s[-1].nom);
    }

    //creation du fichier de sauvegarde des données du joueur
    FILE * file;
    file = fopen(path, "w");
    if(file!=NULL){
        fprintf(file, "%s %d %d %d %d %d %d %d %d %d\n", player.name, genre, x, y, init, init, init, init, init, init);
        fclose(file);
    }else{
        printf("fichier non crée\n");
        return player;
    }
    player.inventaire = player_inventory_create(path);

    //libération mémoire
    free(path);
    return player;
}

player_t player_init(char * file_name){

    player_t player;
    int level, xp, vie, x, y;

    char * path = malloc(sizeof(char)*MAX_LEN_PATH);
    strcpy(path, "include/data/players_data/");
    strcat(path, file_name);

    char * name = malloc(sizeof(char)*MAX_LEN_NAME);
    int genre, sdlon_index[6], i, cpt=0, invent_qtt;

    FILE * file;
    file = fopen(path, "r");

    fscanf(file, "%s %d %d %d %d %d %d %d %d %d\n", name, &genre, &x, &y, &sdlon_index[0], &sdlon_index[1], &sdlon_index[2], &sdlon_index[3], &sdlon_index[4], &sdlon_index[5]);

    player.name = malloc(sizeof(char)*MAX_LEN_NAME);
    strcpy(player.name, name);
    player.genre = genre;
    player.x = x;
    player.y = y;

    for(i=0;sdlon_index[i]!=-1;i++){  
        fscanf(file, "%d %d %d", &level, &xp, &vie);
        strcpy(player.sd[i].nom, malloc(sizeof(char)*MAX_LEN_NAME));
        strcpy(player.sd[i].nom, sdlon_s[sdlon_index[i]].nom);
        player.sd[i].level = level;
        player.sd[i].xp = xp;
        player.sd[i].vie = vie;
        player.sd[i].type = sdlon_s[sdlon_index[i]].type;
        player.sd[i].vie_max = sdlon_s[sdlon_index[i]].vie_max;
        player.sd[i].evolution = sdlon_s[sdlon_index[i]].evolution;
        player.sd[i].evol_sys = sdlon_s[sdlon_index[i]].evol_sys;
        player.sd[i].attaque_1 = sdlon_s[sdlon_index[i]].attaque_1;
        player.sd[i].attaque_2 = sdlon_s[sdlon_index[i]].attaque_2;
        player.sd[i].attaque_3 = sdlon_s[sdlon_index[i]].attaque_3;
        player.sd[i].attaque_4 = sdlon_s[sdlon_index[i]].attaque_4;
        cpt++;
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

/**
 * Libere la mémoire utiliser par le joueurs
*/
int player_quit(player_t * player){
    int i;
    if(player==NULL){
        return 1;
    }
    free(player->name);
    free(player->inventaire.path_to_save);
    
    player->name=NULL;
    return 0;
}

int display_pss(player_t player){
    int i;
    printf("Total de sdlon dans le set: %d\n\n", player.nb_current_sdlon);
    for(i=0;i<player.nb_current_sdlon;i++){
        printf("Sdlon n° %d:\nNom: %s\n\n", i+1, player.sd[i].nom);
    }
    return 0;
}

/**
 * save set, player, item
 * pour sauvegarder ses données
 * dans le bon format
*/
int sspi(player_t player){
    FILE * file;
    int i;
    file = fopen(player.inventaire.path_to_save, "w");

    fprintf(file, "%s %d", player.name, player.genre);

    for(i=0;i<player.nb_current_sdlon;i++){
        fprintf(file, " %d", get_sdlon_index(player.sd[i].nom));
    }
    for(;i<MAIN_MAX;i++){
        fprintf(file, " -1");
    }
    fprintf(file, "\n");

    for(i=0;i<player.nb_current_sdlon;i++){
        fprintf(file, "%d %d %d\n", player.sd[i].level, player.sd[i].xp, player.sd[i].vie);
    }

    for(i=0;i<NB_ITEMS;i++){
        fprintf(file, "%d ", player.inventaire.list_item[i]);
    }

    fclose(file);
    return 1;
}

/**
 * Permet de retourner la quantité
 * d'un item posséder par le joueur
*/
int get_player_item(player_t * player, int num_item){
    return(player->inventaire.list_item[num_item]);
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
int remove_items(int num_item, int qtt, player_t * player){
    int nb_items = player->inventaire.list_item[num_item];

    if(nb_items <= 0){
        return 1;
    }else if((nb_items - qtt) <= 0){
        player->inventaire.list_item[num_item] = 0;
        return (nb_items);
    }else{
        player->inventaire.list_item[num_item] -= qtt;
    }
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
int add_sdlon_in_set(sdlon sd, player_t * player){

    int i = player->nb_current_sdlon;

    if(i>=MAIN_MAX){
        return 1;
    }else{
        strcpy(player->sd[i].nom, sd.nom);
        player->sd[i].level = sd.level;
        player->sd[i].xp = sd.xp;
        player->sd[i].vie = sd.vie;
        player->sd[i].type = sd.type;
        player->sd[i].vie_max = sd.vie_max;
        player->sd[i].evolution = sd.evolution;
        player->sd[i].evol_sys = sd.evol_sys;
        player->sd[i].attaque_1 = sd.attaque_1;
        player->sd[i].attaque_2 = sd.attaque_2;
        player->sd[i].attaque_3 = sd.attaque_3;
        player->sd[i].attaque_4 = sd.attaque_4;
    }
    player->nb_current_sdlon++;
    return 0;
}

/**
 * Fonction qui retire un sdlon
 * de la main courante d'un joueurs
*/
int remove_sdlon_in_set(sdlon sd, player_t * player){
    int nb = player->nb_current_sdlon, i=0, cmp;
    sdlon sd_tmp = player->sd[0];
    cmp = sdloncmp(sd_tmp, sd);
    
    if(nb<=0){
        return 1;
    }else{
        while(cmp && i<nb){
            i++;
            sdlon sd_tmp = player->sd[i];
            cmp = sdloncmp(sd_tmp, sd);
        }
        if(i>=nb){
            player->nb_current_sdlon--;
            return 0;
        }else{
            for(;i<nb;i++){
                player->sd[i] = player->sd[i+1];
            }
            if(i>=nb){
                player->nb_current_sdlon--;
                return 0;
            }
        }
    }
    return 0;
}

/**
 * Fonction qui switch
 * les sdlons du set du joueur
*/
int switch_sdlon_from_set(sdlon sd_in, sdlon sd_out, player_t * player){
    remove_sdlon_in_set(sd_out, player);
    add_sdlon_in_set(sd_in, player);
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
    FILE *f = fopen(name, "r");
    enTeteBox();
    sdlon aux;
    if(f == NULL){
        printf("Erreur d'ouverture du fichier Box SDLon\n");
        return 1;
    }
    while(!feof(f)){
        fscanf(f,"%d %d %d %d %d %d %d %s\n",&aux.type,&aux.vie_max,&aux.vie,&aux.evolution,&aux.level,&aux.evol_sys,&aux.xp,aux.nom); // sauvegarde des infos des SDLons
        fscanf(f,"%d %d %d %s\n",&aux.attaque_1.degat,&aux.attaque_1.mode_attaque,&aux.attaque_1.type_attaque,aux.attaque_1.nom_attaque);//save attaque numero 1
        fscanf(f,"%d %d %d %s\n",&aux.attaque_2.degat,&aux.attaque_2.mode_attaque,&aux.attaque_2.type_attaque,aux.attaque_2.nom_attaque);//save attaque numero 2
        fscanf(f,"%d %d %d %s\n",&aux.attaque_3.degat,&aux.attaque_3.mode_attaque,&aux.attaque_3.type_attaque,aux.attaque_3.nom_attaque);//save attaque numero 3
        fscanf(f,"%d %d %d %s\n",&aux.attaque_4.degat,&aux.attaque_4.mode_attaque,&aux.attaque_4.type_attaque,aux.attaque_4.nom_attaque);//save attaque numero 4
        
        append(&boiteASdlon, aux);
    }

    fclose(f);

    return 0;
}


/**
 * créé une boite
 * dans laquel le joueur
 * pourras stocker ses sdlons
*/
int create_box(){
    boiteASdlon = malloc(sizeof(box));
    boiteASdlon->next = NULL;
    boiteASdlon->precedent = NULL;
    return 0;
}

/*
    fonction sauvegarde de la box
*/

int save_box(char *name){
    FILE *f = fopen(name, "w+");
    enTeteBox();
    sdlon aux = boiteASdlon->current;
    if(f == NULL){
        printf("Erreur d'ouverture du fichier Box SDLon\n");
        return 1;
    }
    while(boiteASdlon->next != NULL){
        fprintf(f,"%d %d %d %d %d %d %d %s\n",aux.type,aux.vie_max,aux.vie,aux.evolution,aux.level,aux.evol_sys,aux.xp,aux.nom); // sauvegarde des infos des SDLons
        fprintf(f,"%d %d %d %s\n",aux.attaque_1.degat,aux.attaque_1.mode_attaque,aux.attaque_1.type_attaque,aux.attaque_1.nom_attaque);//save attaque numero 1
        fprintf(f,"%d %d %d %s\n",aux.attaque_2.degat,aux.attaque_2.mode_attaque,aux.attaque_2.type_attaque,aux.attaque_2.nom_attaque);//save attaque numero 2
        fprintf(f,"%d %d %d %s\n",aux.attaque_3.degat,aux.attaque_3.mode_attaque,aux.attaque_3.type_attaque,aux.attaque_3.nom_attaque);//save attaque numero 3
        fprintf(f,"%d %d %d %s\n",aux.attaque_4.degat,aux.attaque_4.mode_attaque,aux.attaque_4.type_attaque,aux.attaque_4.nom_attaque);//save attaque numero 4
        suivantBox();
        aux = boiteASdlon->current;
    }

    fclose(f);
    return 1;

}

/**
 * fonction de sauvegarde des donnée
 * des datas du joueurs
 * box/set/items
 * optionel en fonction des autres système de sauvegarde de l'initialisation
*/
int save_player_data(char * file_name){
    //optionelle
    //faire à la fin
    //la sauvegarde seras surement gérer autre part
    return 0;
}