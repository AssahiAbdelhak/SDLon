#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
Initialisation macros
*/
#define NB_SDLON 10
#define NB_ATTAQUE 10

/**
Initialisation constantes
*/
const int TYPE_FEU = 0;
const int TYPE_EAU = -1;
const int TYPE_TERRE = 1;

const int JET_LAG = 0;
const int LAGOS = 1;
const int INSERT = 2;
const int RAGE_QUIT = 3;
const int CVSPYTHON = 4;
const int WTF = 5;
const int BDD = 6;
const int CACHETTE = 7;

/**
Initialisation structures
*/
typedef struct struct_attaque {
  char *nom_attaque;
  int type_attaque;
  int mode_attaque;
  int degat;
} attaque;

typedef struct struct_sdlon {
  int type;
  char *nom;
  int vie;
  attaque *attaque_1;
  attaque *attaque_2;
  attaque *attaque_3;
  attaque *attaque_4;
} sdlon;

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

sdlon *sdlon_init(attaque *attaques) {
  /**
  Initialise le pointeur et alloue de la mémoire*/
  sdlon *sdlons = malloc(sizeof(sdlon) * NB_SDLON);

  // sdlon 1
  sdlons->type = TYPE_FEU;
  sdlons->nom = "ram";
  sdlons->vie = 60;
  sdlons->attaque_1 = attaques + JET_LAG;

  // sdlon suivant
  sdlons++;

  // sdlon 2
  sdlons->nom = "tester";
  sdlons->type = TYPE_EAU;
  sdlons->attaque_1 = attaques + LAGOS;

  // on reviens au début
  sdlons--;

  return sdlons;
}

int display_sdlon(sdlon *s) {
  printf("name: %s, type: %i, attaque1: %s\n", s->nom, s->type,
         s->attaque_1->nom_attaque);
  return 0;
}

int main(void) {

  /**
  Déclaration variable
  */
  srand(time(NULL));
  sdlon *sdlons;
  attaque *attaques;

  /**
  Initialisation des sdlons
  */
  attaques = attaque_init();
  sdlons = sdlon_init(attaques);

  /**
  Affiche le sdlon souhaité
  */
  display_sdlon(sdlons + 1);
  display_sdlon(sdlons);

  free(sdlons);
  free(attaques);

  return 0;
}