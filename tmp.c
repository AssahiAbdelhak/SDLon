#include "sdlon_init.h"
#include <stdio.h>
#include <stdlib.h>

/**
Initialisation constantes
*/
const int NB_ATTAQUE = 10;

const int TYPE_FEU = 0;
const int TYPE_EAU = -1;
const int TYPE_TERRE = 1;
const int TYPE_AIR = 2;

const int JET_LAG = 0;
const int LAGOS = 1;
const int INSERT = 2;
const int RAGE_QUIT = 3;
const int CVSPYTHON = 4;
const int WTF = 5;
const int BDD = 6;
const int CACHETTE = 7;

sdlon sdlon_s[NB_SDLON];

/**
Initialisation des sdlons
*/
attaque *attaque_init() {
  // initialise le pointeurs et alloue la mémoire
  attaque *attaques = malloc(sizeof(attaque) * NB_ATTAQUE);

  // attaque 1
  attaques->nom_attaque = "Jet lag";
  attaques->type_attaque = TYPE_FEU;
  attaques->mode_attaque = 1;
  attaques->degat = 10;

  // attaque suivante
  attaques++;

  // attaque 2
  attaques->nom_attaque = "Lagos";
  attaques->type_attaque = TYPE_FEU;
  attaques->mode_attaque = 1;
  attaques->degat = 25;

  // on remet l'adresse à 0
  attaques--;

  return attaques;
}

int sdlon_is_init(sdlon *sd) {
  if (sd == NULL) {
    return 0;
  } else {
    return 1;
  }
}

int attaque_is_init(sdlon *at) {
  if (at == NULL) {
    return 0;
  } else {
    return 1;
  }
}

int sdlon_init_(/*attaque *attaques*/) {
  int i = 0;
  char *name_file = "data/init.txt";
  FILE *file = NULL;

  int type, life;

  char *name_sdlon, *name_evol, *at1, *at2, *at3, *at4;


  file = fopen(name_file, "r");

  if(file!=NULL){
    for(i=0;i<NB_SDLON;i++){
      fscanf(file, "%d %s %d %s %s %s %s %s", &type, name_sdlon ,&life, at1, at2, at3, at4, name_evol);
      //printf("nom: %s, type: %d, evolution: %s");
    }
  }else{
    return 1;
  }

  fclose(file);

  return 0;
  /**
  Initialise le pointeur et alloue de la mémoire*/
  //sdlon *sdlons = malloc(sizeof(sdlon) * NB_SDLON);

  // sdlon 1
  //sdlons->type = TYPE_FEU;
  //sdlons->nom = "ram";
  //sdlons->vie = 60;
  //sdlons->attaque_1 = attaques + JET_LAG;

  // sdlon suivant
  //sdlons++;

  // sdlon 2
  //sdlons->nom = "tester";
  //sdlons->type = TYPE_EAU;
  //sdlons->attaque_1 = attaques + LAGOS;

  // on reviens au début
  //sdlons--;

  //return sdlons;
}

int display_sdlon(sdlon *s) {
  switch (s->type) {
  case 0:
    printf("name: %s, type: feu, attaque1: %s\n\n", s->nom,
           s->attaque_1->nom_attaque);
    break;
  case 1:
    printf("name: %s, type: terre, attaque1: %s\n\n", s->nom,
           s->attaque_1->nom_attaque);
    break;
  case 2:
    printf("name: %s, type: air, attaque1: %s\n\n", s->nom,
           s->attaque_1->nom_attaque);
    break;
  case -1:
    printf("name: %s, type: eau, attaque1: %s\n\n", s->nom,
           s->attaque_1->nom_attaque);
    break;
  }

  return 0;
}

int sdlon_quit(sdlon *sdlons, attaque *attaques) {
  free(sdlons);
  free(attaques);
  sdlons = NULL;
  attaques = NULL;
  return 0;
}












/////////////////////////////////////////////////////////


























/**
  Test d'initialisation d'un tableau de sdlon inexistant
  */
  //printf("Test d'initialisation sur un tableau de sdlon non-initialiser:\n");
  //sdlon_is_init(sdlons) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  /**
  Test d'initialisation d'un tableau d'attaque inexistant
  */
  //printf("Test d'initialisation sur un tableau de sdlon non-initialiser:\n");
  //attaque_is_init(attaques) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  /**
  Initialisation des sdlons
  */
  //attaques = attaque_init();
  //sdlons = sdlon_init(attaques);

  /**
  Test d'initialisation d'un tableau de sdlon existant
  */
  //printf("Test d'initialisation sur un tableau de sdlon initialiser:\n");
  //!sdlon_is_init(sdlons) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  /**
  Test d'initialisation d'un tableau d'attaque existant
  */
  //printf("Test d'initialisation sur un tableau de sdlon non-initialiser:\n");
  //!attaque_is_init(attaques) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  /**
  Test d'affichage d'accès au donnée
  */
  //printf("Test d'affichage pour vérifier la concordance des données:\n");
  //display_sdlon(sdlons);

  /**
  Libération mémoire et pointeur
  */
  //sdlon_quit(sdlons, attaques);

  /**
  Test d'initialisation d'un tableau de sdlon quitter
  */
  //printf("Test d'initialisation sur un tableau de sdlon quitter:\n");
  //sdlon_is_init(sdlons) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  /**
  Test d'initialisation d'un tableau d'attaque quitter
  */
  //printf("Test d'initialisation sur un tableau de sdlon quitter:\n");
  //attaque_is_init(attaques) ? printf("-->KO\n\n") : printf("-->OK\n\n");
