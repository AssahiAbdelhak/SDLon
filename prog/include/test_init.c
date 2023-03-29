/**
* @file test_init.c
* Fichier de tests et de debogage
* @author Wandrille Ballereau
* @author Abdelhak Assahi
* @author Lilian Colla
* @author Mohamed Besbes
* @date 2023
* @version 1.0 Alpha
*
*/
#include "Primitives_Box.h"
#include "sdlon_generate.h"
#include "combat.h"
#include "test_header.h"
#include "player.h"
#include "item.h"
#include "story.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * @brief jeu de tests et de debogage
*/
int main(int argc, char * argv[]) {

  int test=0, verbose = 0, cpt=40, error=0, i;
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
  nb_gen=0;

  for(i=0;i<cpt;i++){
    if(!test && sd_target.vie == sd_target.vie_max){
      nb_gen++;
    }else if(test == 1 && sd_target.vie < sd_target.vie_max){
      nb_gen++;
    }else if(test == 2 && sd_src.vie == sd_src.vie_max){
      nb_gen++;
    }else{
      error=1;
    }

    sd_src = generate_sdlon(0,45,75);
    sd_target = generate_sdlon(0,45,75);
    test = sats(&sd_src, &sd_target, 1);
  }
  
  nega_test_print(error, verbose);
  affiche_fiability("de la fonction 'sats'", NB_SDLON, nb_gen, verbose);
  error=0;

  //test des fonctions de combats (ia)
  affiche_test("de la fonction de combat 'ia'", verbose);
  sd_src = generate_sdlon(0,45,75);
  sd_target = generate_sdlon(0,45,75);
  test = ia(&sd_src, &sd_target);
  posi_test_print(test, verbose);

  //test création du joueurs
  affiche_test("de la création du joueur", verbose);
  player_t p_homme = player_create("coco", HOMME, "coco");
  player_t p_femme = player_create("cocotte", FEMME, "cocotte");
  error=0;
  if(!strcmp(p_homme.name, "coco") && !strcmp(p_femme.name, "cocotte") &&
  p_homme.genre == HOMME && p_femme.genre == FEMME){ 
    //verification des sdlons (var p_femme)
    for(i=0;i<MAIN_MAX;i++){
      if(strcmp(p_femme.sd[i].nom, sdlon_s[-1].nom)){
        error=1;
      }
    }
    //verification des sdlons (var p_homme)
    for(i=0;i<MAIN_MAX;i++){
      if(strcmp(p_homme.sd[i].nom, sdlon_s[-1].nom)){
        error=1;
      }
    }
  }else{
    error=1;
  }
  nega_test_print(error, verbose);
  player_quit(&p_femme);
  player_quit(&p_homme);

  //test d'initialisation du joueurs
  char * save_file = malloc(sizeof(char)*80);
  strcpy(save_file, "coco");
  affiche_test("de l'initialisation du joueur", verbose);
  player_t player_test = player_init(save_file);
  //printf("%s, %d, %s, %d, %s, %d\n", player_test.name, player_test.inventaire.list_item[0], player_test.inventaire.path_to_save, player_test.inventaire.max_item_per_slot, player_test.sd[0].nom, player_test.sd[0].level);
  error=0;
  if(strcmp(save_file, player_test.name)){
    error = 1;
  }
  free(save_file);
  error += player_quit(&player_test);
  nega_test_print(error, verbose);

  //test d'initialisation des items
  affiche_test("de l'initialisation des items", verbose);
  error = item_init();
  nega_test_print(error, verbose);

  //affichage des items pour tester
  //display_all_items();

  //test d'accès aux items (sur un item vide)
  affiche_test("de l'accès aux items (sur un item vide)", verbose);
  player_t player = player_create("test", 0, "test");
  int qtt_sdlasso = get_player_item(&player, SDLASSO);
  //printf("nb sdlasso: %d\n", qtt_sdlasso);
  nega_test_print(qtt_sdlasso, verbose);

  //test d'ajout d'un item
  affiche_test("de l'accès aux items (sur un item non-vide)", verbose);
  error = add_items(SDLASSO, 5, &player);
  nega_test_print(error, verbose);
  //qtt_sdlasso = get_player_item(&player, SDLASSO);
  //printf("nb sdlasso: %d\n", qtt_sdlasso);

  //test d'ajout d'un sdlon dans le set du joueur
  affiche_test("d'ajout d'un sdlon dans le set d'un joueur", verbose);
  error += add_sdlon_in_set(sdlon_s[0], &player);
  error += add_sdlon_in_set(sdlon_s[5], &player);
  error += add_sdlon_in_set(sdlon_s[3], &player);
  error += add_sdlon_in_set(sdlon_s[3], &player);
  error += add_sdlon_in_set(sdlon_s[8], &player);
  error += add_sdlon_in_set(sdlon_s[9], &player);
  nega_test_print(error, verbose);

  affiche_test("d'ajout d'un sdlon dans le set complet d'un joueur", verbose);
  error=0;
  error += add_sdlon_in_set(sdlon_s[9], &player);
  posi_test_print(error, verbose);
  sspi(player);

  //visualisation des sdlons dans le set d'un joueur
  display_pss(player);

  remove_sdlon_in_set(player.sd[5], &player);

  //visualisation des sdlons dans le set d'un joueur
  display_pss(player);

  //switch de 2 sdlons
  switch_sdlon_from_set(sdlon_s[2], player.sd[4], &player);

  //visualisation des sdlons dans le set d'un joueur
  display_pss(player);

  //test de sortie des items
  affiche_test("de sortie des items ('quit')", verbose);
  test = item_quit();
  posi_test_print(test, verbose);
  player_quit(&player);



  town_init();

  display_town(all_town[0]);
}