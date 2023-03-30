/**
* @file story.c
* Fichier gestion de l'histoire, des pnj et de la map 
* @author Wandrille Ballereau
* @author Abdelhak Assahi
* @author Lilian Colla
* @author Mohamed Besbes
* @date 2023
* @version 1.0 Alpha
*
*/
#include "story.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdlon_generate.h"

//gestion des pnj
//gestion de l'histoire du jeu
//gestion de la map en elle même

town_t all_town[NB_TOWN];

/**
 * @brief Fonction qui initialise les villes
*/
void town_init(){
    char * path = "include/data/init_town.txt";
    char * name = malloc(sizeof(char)*MAX_LEN_NAME);
    char * source_grid = malloc(sizeof(char)*MAX_LEN_NAME);
    int i=0, j=0, k=0, nb_town, badge_required, type_map, environnement, nb_layer, nb_tiles, tile_width, tile_height, first_grid, value;
    char sep;
    FILE * file;

    file = fopen(path, "r");
    fscanf(file, "%d\n", &nb_town);

    for(i=0;i<nb_town;i++){
        fscanf(file, "%s %d %d %d %d %d %d %d %d %s\n", name, &badge_required, &type_map, &environnement, &nb_layer, &nb_tiles, &tile_width, &tile_height, &first_grid, source_grid);
        all_town[i].name = malloc((sizeof(char)*MAX_LEN_NAME));
        all_town[i].source_grid = malloc((sizeof(char)*MAX_LEN_PATH));
        strcpy(all_town[i].name, name);
        strcpy(all_town[i].source_grid, source_grid);
        all_town[i].badge_required = badge_required;
        all_town[i].type_map = type_map;
        all_town[i].environnement = environnement;
        all_town[i].nb_layer = nb_layer;
        all_town[i].nb_tiles = nb_tiles;
        all_town[i].tile_width = tile_width;
        all_town[i].tile_height = tile_height;
        all_town[i].first_grid = first_grid;
        all_town[i].source_grid = source_grid;
        fscanf(file, "%d%c", &value, &sep);
        for(j=0;j<nb_layer;j++){
            while(sep != '\n'){
                all_town[i].layer[j][k] = value;
                fscanf(file, "%d%c", &value, &sep);
                k++;
            }
            fscanf(file, "%d%c", &value, &sep);
            k=0;
        }
    }

    fclose(file);
    free(name);    
}


/**
 * @brief Fonction qui affiche les specs d'une ville
 * Permet de débuger plus facilement les erreurs
*/
void display_town(town_t town){
    printf("Nom de la ville: %s\n", town.name);
    printf("Environnement de la ville: %d\n", town.environnement);
    printf("Nombre de badge requis: %d\n", town.badge_required);
    printf("Type de ville: %d\n", town.type_map);
    printf("First grid: %d\n", town.first_grid);
    printf("Source grid: %s\n", town.source_grid);
    printf("Hauteur des tuiles: %d\n", town.tile_height);
    printf("Largeur des tuiles: %d\n", town.tile_width);
    return ;
}


/**
 * @brief Vérifie que l'on peu aller dans la ville suivante
 * En ayant complété l'histoire du jeu
 * dans la ville actuelle
 * Passage dans la ville suivante nécéssite l'obtention du badge
*/
int can_next_town(player_t player, town_t town){
    return(town.badge_required<=player.badges);
}
/**
 * @brief retourne le type de la map (eau/feu/terre/air)
*/
int get_town_environnement(town_t town){
    return town.environnement;
}

/**
 * @brief retourne le sdlon choisi par le joueur
*/
sdlon choix(int i){
    switch(i){
        case 1:
            return assign_sd(0,4,7);
        case 2:
            return assign_sd(7,4,7);
        case 3:
            return assign_sd(16,4,7);
    }
    return ;
}