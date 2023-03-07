#include "sdlon_generate.h"
#include "combat.h"
#include <stdio.h>

/**
 * affiche l'etat du test
 * dans le cas ou le resultat du test = 1
*/
void posi_test_print(int test, int verbose){

  if(verbose){
    test? printf("-->OK\n\n"):printf("-->KO\n\n");
  }
  
  return;
}

/**
 * affiche l'etat du test
 * dans le cas ou le resultat du test = 0
*/
void nega_test_print(int test, int verbose){

  if(verbose){
    !test? printf("-->OK\n\n"):printf("-->KO\n\n");
  }
  
  return;
}

/**
 * Affiche le test actuelle
*/
void affiche_test(char * str, int verbose){
  if(verbose){
    printf("---Test %s:\n", str);
  }
  
  return;
}

int main(int argc, char * argv[]) {

  int test=0, verbose = 0, cpt=4000, error=0, i;
  float nb_gen=0;

  if(argc == 2){
    verbose = 1;
  }

  //test d'initialisation des sdlons
  affiche_test("d'initialisation des sdlons", verbose);
  test = sdlon_init();
  nega_test_print(test, verbose);

  //test de génération de sdlons aux bornes 1 -> 15
  affiche_test("de génération aux bornes 1 -> 15", verbose);
  for (i = 0; i < cpt; i++)
  {
    sdlon sd = generate_sdlon(0,1,15);
    nb_gen++;
    if(sd.level < 1 || sd.level > 15){
      error = 1;
    }
  }
  nega_test_print(error, verbose);
  error=0;

  //test de génération de sdlons aux bornes 15 -> 35
  affiche_test("de génération aux bornes 15 -> 35", verbose);
  for (i = 0; i < cpt; i++)
  {
    sdlon sd = generate_sdlon(0,15,35);
    nb_gen++;
    if(sd.level < 15 || sd.level > 35){
      error = 1;
    }
  }
  nega_test_print(error, verbose);
  error=0;

  //test de génération de sdlons aux bornes 35 -> 45
  affiche_test("de génération aux bornes 35 -> 45", verbose);
  for (i = 0; i < cpt; i++)
  {
    sdlon sd = generate_sdlon(0,35,45);
    nb_gen++;
    if(sd.level < 35 || sd.level > 45){
      error = 1;
    }
  }
  nega_test_print(error, verbose);
  error=0;

  //test de génération de sdlons aux bornes 45 -> 75
  affiche_test("de génération aux bornes 45 -> 75", verbose);
  for (i = 0; i < cpt; i++)
  {
    sdlon sd = generate_sdlon(0,45,75);
    nb_gen++;
    if(sd.level < 45 || sd.level > 75){
      error = 1;
    }
  }
  nega_test_print(error, verbose);
  error=0;
  
  //affichage de la fiabilité des génération
  printf("Fiabilité de génération: %0.3f\n", 1-(NB_SDLON/nb_gen));

  return 0;
}