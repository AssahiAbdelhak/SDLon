#include "sdlon_generate.h"
#include "combat.h"
#include "test_header.h"
#include <stdio.h>

int main(int argc, char * argv[]) {

  int test=0, verbose = 0, cpt=4000, error=0, i;
  float nb_gen=0;

  if(argc >= 2){
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
  affiche_fiability("génération des sdlons", NB_SDLON, nb_gen, verbose);

  //test des fonctions de combats (sats)
  affiche_test("de la fonction de combat 'sats'", verbose);
  sdlon sd_src = generate_sdlon(0,45,75);
  sdlon sd_target = generate_sdlon(0,45,75);
  test = sats(&sd_src, &sd_target, 1);

  if(!test && sd_target.vie == sd_target.vie_max){
    nega_test_print(test, verbose);
  }else if(test == 1 && sd_target.vie < sd_target.vie_max){
    posi_test_print(test, verbose);
  }else if(test == 2 && sd_src.vie == sd_src.vie_max){
    posi_test_print(test, verbose);
  }else{
    nega_test_print(1, verbose);
  }

  //printf("Dégâts apply, v=%d, vm=%d\n", sd_target->vie, sd_target->vie_max);
  return 0;
}