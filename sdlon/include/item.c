#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

item_t items[NB_ITEMS];

int item_init(){
    int i = 0, type, usage, opt_degat, opt_tag;
    char *name_file = "data/init_item.txt";
    char *name=malloc(sizeof(char)*50);
    char *descritpion=malloc(sizeof(char)*250);
    FILE *file = NULL;

    file = fopen(name_file, "r");

    if(file!=NULL){
        for(i=0;i<NB_ITEMS;i++){
            items[i].name = malloc(sizeof(char)*50);
            items[i].description = malloc(sizeof(char)*250);
            fscanf(file, "%s %s %d %d %d %d\n", name, descritpion, &type, &usage, &opt_degat, &opt_tag);
            strcpy(items[i].name, name);
            strcpy(items[i].description, descritpion);
            items[i].type = type;
            items[i].usage = usage;
            items[i].opt_degat = opt_degat;
            items[i].opt_tag = opt_tag;
        }
    }else{
        return 1;
    }

    fclose(file);
    free(name);
    free(descritpion);

    return 0;
}

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

int display_all_items(){
    int i;
    for(i=0;i<NB_ITEMS;i++){
        printf("Item n°%d:\nNom: %s.\ndescription: %s.\nopt_degat: %d.\n\n", i+1, items[i].name, items[i].description, items[i].opt_degat);
    }
    return 1;
}