/**
* @file item.c
* Fichier des items
* @author Wandrille Ballereau
* @author Abdelhak Assahi
* @author Lilian Colla
* @author Mohamed Besbes
* @date 2023
* @version 1.0 Alpha
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

item_t items[NB_ITEMS];
/**
 * @brief initialise le tableau d'item en fonction du fichier d'entrée
*/
int item_init(){
    int i = 0, type, usage, opt_degat, opt_tag, prix;
    char *name_file = "include/data/init_item.txt";
    char *name=malloc(sizeof(char)*MAX_LEN_NAME);
    char *descritpion=malloc(sizeof(char)*MAX_LEN_DESCR);
    char *image_path=malloc(sizeof(char)*MAX_LEN_PATH);
    FILE *file = NULL;

    file = fopen(name_file, "r");

    if(file!=NULL){
        for(i=0;i<NB_ITEMS;i++){
            items[i].name = malloc(sizeof(char)*MAX_LEN_NAME);
            items[i].description = malloc(sizeof(char)*MAX_LEN_DESCR);
            items[i].path = malloc(sizeof(char)*MAX_LEN_PATH);
            fscanf(file, "%s %[^\n]%d %d %d %d %d %s\n", name, descritpion, &type, &usage, &opt_degat, &opt_tag, &prix, image_path);
            strcpy(items[i].path, image_path);
            strcpy(items[i].name, name);
            strcpy(items[i].description, descritpion);
            items[i].prix = prix;
            items[i].type = type;
            items[i].usage = usage;
            items[i].opt_degat = opt_degat;
            items[i].opt_tag = opt_tag;
        }
    }else{
        SDL_Log("Erreur d'ouverture de fichier");
        return 1;
    }

    fclose(file);
    free(name);
    free(descritpion);

    return 0;
}
/**
 * @brief libere la memoire
*/
int item_quit(){
    int i;
    for(i=0;i<NB_ITEMS;i++){
        free(items[i].name);
        free(items[i].description);
        items[i].name = NULL;
        items[i].description = NULL;
    }
    return 1;
}
/**
 * @brief affichage des items "debogage"
*/
int display_all_items(){
    int i;
    SDL_Log("Début de l'affichage de tous les items:\n");
    for(i=0;i<NB_ITEMS;i++){
        printf("Item n°%d:\nNom: %s.\ndescription: %s.\nopt_degat: %d.\n\n", i+1, items[i].name, items[i].description, items[i].opt_degat);
    }
    return 1;
}