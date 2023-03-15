#include "story.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//gestion des pnj
//gestion de l'histoire du jeu
//gestion de la map en elle même

town_t all_town[NB_TOWN];

/**
 * Fonction qui initialise les villes
*/
void town_init(){
    char * path = "data/init_town.txt";
    char * name = malloc(sizeof(char)*MAX_LEN_NAME);
    int i=0, j=0, k=0, nb_town, badge_required, type_map, environnement, nb_layer, nb_tiles, tile_width, tile_height, first_grid, source_grid, value;
    char sep;
    FILE * file;

    file = fopen(path, "r");
    fscanf(file, "%d\n", &nb_town);

    for(i=0;i<nb_town;i++){
        fscanf(file, "%s %d %d %d %d %d %d %d %d %d\n", name, &badge_required, &type_map, &environnement, &nb_layer, &nb_tiles, &tile_width, &tile_height, &first_grid, &source_grid);
        strcmp(all_town[i].name, name);
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
 * Vérifie que l'on peu aller dans la ville suivante
 * En ayant complété l'histoire du jeu
 * dans la ville actuelle
 * Passage dans la ville suivante nécéssite l'obtention du badge
*/
int can_next_town(player_t player, town_t town){
    return(town.badge_required<=player.badges);
}

int get_town_environnement(town_t town){
    return town.environnement;
}