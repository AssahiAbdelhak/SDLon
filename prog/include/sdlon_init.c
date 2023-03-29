/**
* @file sdlon_init.c
* Fichier d'initialisation des sdlons 
* @author Wandrille Ballereau
* @author Abdelhak Assahi
* @author Lilian Colla
* @author Mohamed Besbes
* @date 2023
* @version 1.0 Alpha
*
*/
#include "sdlon_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
*@brief Déclaration des tableaux de sdlons & attaques
*/
sdlon sdlon_s[NB_SDLON];
attaque attaque_s[NB_SDLON];

/**
*@brief Fonction d'initialisation du tableau d'attaques
*/
int attaque_init() {
  int i = 0;
  char *name_file = "include/data/init_at.txt";
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

/**
* @brief Fonction d'initialisation du tableau de sdlons
*/
int sdlon_init() {

  attaque_init();

  int i = 0;
  char *name_file = "include/data/init_sd.txt";
  FILE *file = NULL;

  int type, life, at1, at2, at3, at4, evol, level, evol_sys;

  char name_sdlon[50];
  char front_face[200];
  char back_face[200];


  file = fopen(name_file, "r");

  if(file!=NULL){
    for(i=0;i<NB_SDLON;i++){
      fscanf(file, "%d %s %d %d %d %d %d %d %d %d %s %s\n", &type, name_sdlon, &life, &at1, &at2, &at3, &at4, &evol, &level, &evol_sys, front_face, back_face);
      sdlon_s[i].type = type;
      sdlon_s[i].vie_max = life;
      sdlon_s[i].vie = life;
      strcpy(sdlon_s[i].nom, name_sdlon);
      strcpy(sdlon_s[i].front_face, front_face);
      strcpy(sdlon_s[i].back_face, back_face);
      sdlon_s[i].attaque_1 = attaque_s[at1];
      sdlon_s[i].attaque_2 = attaque_s[at2];
      sdlon_s[i].attaque_3 = attaque_s[at3];
      sdlon_s[i].attaque_4 = attaque_s[at4];
      sdlon_s[i].evolution = evol;
      sdlon_s[i].level = level;
      sdlon_s[i].evol_sys = evol_sys;

    }
  }else{
    SDL_Log("le fichier n'est pas ouvert\n");
    return 1;
  }

  fclose(file);
  SDL_Log("nom de sdlon_s[0] : %s\n",sdlon_s[0].nom);
  return 0;
}
/**
 * @brief recupere l'indice d'un sdlon depuis le tableau
*/
int get_sdlon_index(char * name){
  int i = 0;
  while(strcmp(sdlon_s[i].nom, name)){
    i++;
  }
  return i;
}
/**
 * @brief compare les sdlons retourne 1 si ils sont differents
*/
int sdloncmp(sdlon sd_src, sdlon sd_origin){
  int diff = 0;
  diff += strcmp(sd_src.nom, sd_origin.nom);
  if(sd_src.evol_sys != sd_origin.evol_sys){
    diff++;
  }
  if(sd_src.evolution != sd_origin.evolution){
    diff++;
  }
  if(sd_src.level != sd_origin.level){
    diff++;
  }
  if(sd_src.type != sd_origin.type){
    diff++;
  }
  if(sd_src.vie != sd_origin.vie){
    diff++;
  }
  if(sd_src.vie_max != sd_origin.vie_max){
    diff++;
  }
  if(sd_src.xp != sd_origin.xp){
    diff++;
  }
  return (diff);
}

/**
* @brief afficher un sdlon s
*/

extern void afficheSDLon(sdlon s){
  switch (s.type)
  {
  case 0:
    /* code */
    printf("\nType : eau\n");
    break;
  case 1:
    /* code */
    printf("\nType : terre\n");
    break;
  case 2:
    /* code */
    printf("\nType : air\n");
    break;
  case 3:
    /* code */
    printf("\nType : feu\n");
    break;
  }
  printf("nom : %s\nvie : %d\nvie max : %d\nattaque 1 : %s\nattaque 2 : %s\nattaque 3 : %s\nattaque 4 : %s\nevolution : %d\nLevel : %d\nEvol_sys : %d\nXp : %d\n",s.nom,s.vie,s.vie_max,s.attaque_1.nom_attaque,s.attaque_2.nom_attaque,s.attaque_3.nom_attaque,s.attaque_4.nom_attaque,s.evolution,s.level,s.evol_sys,s.xp);

}