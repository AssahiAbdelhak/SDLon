#include "sdlon_init.h"
#include <stdio.h>

int main() {
  /**
  Déclaration variable
  */
  sdlon *sdlons;
  attaque *attaques;

  sdlons = NULL;
  attaques = NULL;

  /**
  Test d'initialisation d'un tableau de sdlon inexistant
  */
  printf("Test d'initialisation sur un tableau de sdlon non-initialiser:\n");
  sdlon_is_init(sdlons) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  /**
  Test d'initialisation d'un tableau d'attaque inexistant
  */
  printf("Test d'initialisation sur un tableau de sdlon non-initialiser:\n");
  attaque_is_init(attaques) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  /**
  Initialisation des sdlons
  */
  attaques = attaque_init();
  sdlons = sdlon_init(attaques);

  /**
  Test d'initialisation d'un tableau de sdlon existant
  */
  printf("Test d'initialisation sur un tableau de sdlon initialiser:\n");
  !sdlon_is_init(sdlons) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  /**
  Test d'initialisation d'un tableau d'attaque existant
  */
  printf("Test d'initialisation sur un tableau de sdlon non-initialiser:\n");
  !attaque_is_init(attaques) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  /**
  Test d'affichage d'accès au donnée
  */
  printf("Test d'affichage pour vérifier la concordance des données:\n");
  display_sdlon(sdlons);

  /**
  Libération mémoire et pointeur
  */
  sdlon_quit(sdlons, attaques);

  /**
  Test d'initialisation d'un tableau de sdlon quitter
  */
  printf("Test d'initialisation sur un tableau de sdlon quitter:\n");
  sdlon_is_init(sdlons) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  /**
  Test d'initialisation d'un tableau d'attaque quitter
  */
  printf("Test d'initialisation sur un tableau de sdlon quitter:\n");
  attaque_is_init(attaques) ? printf("-->KO\n\n") : printf("-->OK\n\n");

  return 0;
}