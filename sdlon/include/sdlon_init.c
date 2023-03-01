#include "sdlon_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Déclaration des tableaux de sdlons & attaques
*/
sdlon sdlon_s[NB_SDLON];
attaque attaque_s[NB_SDLON];

/*
Fonction d'initialisation du tableau d'attaques
**/
int attaque_init() {
  int i = 0;
  char *name_file = "data/init_at.txt";
  FILE *file = NULL;

  int type, mode, degat;

  char name_attaque[50];


  file = fopen(name_file, "r");

  if(file!=NULL){
    for(i=0;i<NB_ATTAQUE;i++){
      fscanf(file, "%s %d %d %d\n", name_attaque, &type, &mode, &degat);
      strcpy(attaque_s[i].nom_attaque, name_attaque);
      attaque_s[i].type_attaque = type;
      attaque_s[i].mode_attaque = mode;
      attaque_s[i].degat = degat;
      
    }
  }else{
    return 1;
  }

  fclose(file);

  return 0;
}

/*
Fonction d'initialisation du tableau de sdlons
**/
int sdlon_init() {

  attaque_init();

  int i = 0;
  char *name_file = "data/init_sd.txt";
  FILE *file = NULL;

  int type, life, at1, at2, at3, at4, evol, level, evol_sys;

  char name_sdlon[50];


  file = fopen(name_file, "r");

  if(file!=NULL){
    for(i=0;i<NB_SDLON;i++){
      fscanf(file, "%d %s %d %d %d %d %d %d %d %d\n", &type, name_sdlon, &life, &at1, &at2, &at3, &at4, &evol, &level, &evol_sys);
      sdlon_s[i].type = type;
      sdlon_s[i].vie_max = life;
      strcpy(sdlon_s[i].nom, name_sdlon);
      sdlon_s[i].attaque_1 = attaque_s[at1];
      sdlon_s[i].attaque_2 = attaque_s[at2];
      sdlon_s[i].attaque_3 = attaque_s[at3];
      sdlon_s[i].attaque_4 = attaque_s[at4];
      sdlon_s[i].evolution = evol;
      sdlon_s[i].level = level;
      sdlon_s[i].evol_sys = evol_sys;
    }
  }else{
    return 1;
  }

  fclose(file);

  return 0;
}