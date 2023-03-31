/**
* @file combat.c
* Fichier de gestion des attaques
* @author Wandrille Ballereau
* @author Abdelhak Assahi
* @author Lilian Colla
* @author Mohamed Besbes
* @date 2023
* @version 1.0 Alpha
*
*/
#include "combat.h"
#include "player.h"
#include "item.h"
#include "sdlon_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Si vie en mois, on heal
 * sinon retour
 * retourne 0 si réussis
 * 1 sinon
*/
int heal(sdlon * sd, int value){

    if(sd->vie == sd->vie_max){
        return 0;
    }else{
        sd->vie+=value;
        if(sd->vie > sd->vie_max){
            sd->vie = sd->vie_max;
        }
        return 0;
    }

    return 1;
}

/**
 * @brief Calcul le nombre de degat 
 * en fonction du type
*/
int conf_dgt(int degat, int type_at, int type_target){

    if(type_at==type_target){
        return degat;

    }else if(type_at==EAU){

        if(type_target==FEU){
            return (degat*1.35);
        }else if(type_target==AIR){
            return (degat*0.65);
        }else{
            return degat;
        }

    }else if(type_at==TERRE){

        if(type_target==AIR){
            return (degat*1.35);
        }else if(type_target==FEU){
            return (degat*0.65);
        }else{
            return degat;
        }

    }else if(type_at==AIR){

        if(type_target==EAU){
            return (degat*1.35);
        }else if(type_target==TERRE){
            return (degat*0.65);
        }else{
            return degat;
        }

    }else{

        if(type_target==TERRE){
            return (degat*1.35);
        }else if(type_target==EAU){
            return (degat*0.65);
        }else{
            return degat;
        }

    }
}
/**
* @brief applique les degats sur un sdlon
*/
int apply_attaque(sdlon *sd, int degat){
    
    srand(time(NULL));
    int success_seed = (rand()%100);

    if(success_seed <= 95){
        sd->vie -= degat;
        return 1;
    }else{
        return 0;
    }
    
}
/**
* @brief applique une attaque
*/
int sats(sdlon * sd_at, sdlon * sd_target, int num_at){

    attaque at;
    int type_at, mode_at, degat_at, degat_current;

    //récupération de l'attaque voulus
    switch (num_at)
    {
    case 1:
        at = sd_at->attaque_1;
        break;
    case 2:
        at = sd_at->attaque_2;
        break;
    case 3:
        at = sd_at->attaque_3;
        break;
    case 4:
        at = sd_at->attaque_4;
        break;
    default:
        break;
    }


        // on récupère les specs de l'attaque
        mode_at = at.mode_attaque;
        degat_at = at.degat;
        type_at = at.type_attaque;

        /**
         * selon le mode de l'attaque on fait différent traitement
         * 0: on heal
         * 1: on attaque
        */
        if(mode_at == HEAL){
            if(!heal(sd_at, degat_at)){
                return 2;
            }
        }else{
          degat_current =0;
            degat_current = conf_dgt(degat_at, type_at, sd_target->type);
            printf("degats apportes %d",degat_current);
            if(apply_attaque(sd_target, degat_current)){
                return 1;
            }else{
                return 0;
            }
        }
        return -1;
}

/**
 * @brief Retourne le nombre de sdlons utilisables
*/
int get_usable_sdlon(player_t player){
  int i = 0, cpt=0;
  for(i=0;i<player.nb_current_sdlon;i++){
    if(player.sd[i].vie > 0){
      cpt++;
    }
  }
  return cpt;
}

/**
 * @brief renvoie le status d'un combat
 * 0: gagné
 * 1: sdlon tué mais d'autre en rab
 * 2: continue
 * 3: défaite
*/
int status_combat(player_t player, sdlon sd){
  if(player.sd[player.sd_in_use].vie<=0){
    if(get_usable_sdlon(player) > 0){
      return 1;//on en as encore dans notre set!
    }else{
      return 3;//on as perdu!
    }
  }else if(sd.vie > 0){
    return 2;//on continue
  }else{
    return 0;//on as gagné
  }
}

/**
 * @brief Fonction qui renvoie:
 * 1 si l'on peu se battre
 * 0 sinon
*/
int can_fight(player_t player){
  if(get_usable_sdlon(player)){
    return 1;
  }
    return 0;
}

int get_evolution(sdlon *sd){//erreur de pointeur, variable détruite après
  if(sd->evolution!=0){
    if((sdlon_s[(sd->evolution)].level) <= (sd->level)){
      //assign les spec
      printf("On évolue\n");
      sdlon sd_stock;
      sd_stock = sdlon_s[sd->evolution];
      sd_stock.level = sd->level;
      sd_stock.vie = sd->vie;
      sd_stock.xp = sd->xp;
      *sd = sd_stock;
      printf("Nom évol: %s\n", sd->nom);
      return 1;
    }else{return 0;}
  }else{
    return 0;
  }
}

/**
 * @brief Fonction qui gère le gain de niveau d'un sdlon
 * retourne 1 si le sdlon grimpe de niveau
 * 0 sinon
*/
int get_level(sdlon *sd){
  if(sd->xp<100){
    return 0;
  }else if(sd->xp>100){
    sd->level++;
    sd->xp=(sd->xp-100);
    get_evolution(sd);
    printf("Nom évol: %s\n", sd->nom);
  }
  return 1;
}

/**
 * @brief Fonction qui gère le gain d'expérience
 * retourne le nombre de sdlon ayant grimper de niveau
*/
int get_xp(player_t *player){
  int i=0, cpt=0;
  for(i=0;i<player->nb_current_sdlon;i++){
    player->sd[i].xp += (100-player->sd[i].level);
    cpt += get_level(&(player->sd[i]));
    printf("Nom évol: %s\n", player->sd[i].nom);
  }
  return cpt;
}

/**
 * @brief Fonction retournant un gain ($) après une victoire
*/
int get_loot(player_t *player){
  int loot = (rand()%MAX_GAIN)+1;
  player->argent += loot;
  printf("le loot gagné est de: %d", loot);
  return loot;
}

/**
 * @brief Fonction qui retourne le numero d'attaque a utiliser par l'ordinateur
*/

int ia(sdlon *sd_at, sdlon *sd_target) { // retourne le numero d'attaque a utiliser

  float pv; // pourcentage de vie
  pv = (sd_at->vie / sd_at->vie_max) * 100;
  int chance = (rand() % 100);

  // choix d'une attaque si un one-shot est possible
  if ((sd_at->attaque_1.degat >= sd_target->vie) && sd_at->attaque_1.mode_attaque &&
      chance >= 25) { // 75% de chance

    return 1;

  }if ((sd_at->attaque_2.degat >= sd_target->vie) && sd_at->attaque_2.mode_attaque &&
      chance >= 25) {

    return 2;

  }if ((sd_at->attaque_3.degat >= sd_target->vie) && sd_at->attaque_3.mode_attaque &&
      chance >= 25) {

    return 3;
    
  }if ((sd_at->attaque_4.degat >= sd_target->vie) && sd_at->attaque_4.mode_attaque &&
      chance >= 25) {

    return 4;
  }

  if (pv <= 10 && chance >= 50 ) { // si un SDLon a moins de 10% de vie il se heal

    if (sd_at->attaque_1.mode_attaque == HEAL) {

      return 1;
    }

    if (sd_at->attaque_2.mode_attaque == HEAL) {

      return 2;
    }

    if (sd_at->attaque_3.mode_attaque == HEAL) {

      return 3;
    }

    if (sd_at->attaque_4.mode_attaque == HEAL) {

      return 4;
    }

  } else {

    switch (sd_target->type) { // choix de l'attaque la plus optimiser

    case EAU:

      if (sd_at->attaque_1.type_attaque == AIR && sd_at->attaque_1.mode_attaque)
        return 1;

      if (sd_at->attaque_2.type_attaque == AIR && sd_at->attaque_2.mode_attaque)
        return 2;

      if (sd_at->attaque_3.type_attaque == AIR && sd_at->attaque_3.mode_attaque)
        return 3;

      if (sd_at->attaque_4.type_attaque == AIR && sd_at->attaque_4.mode_attaque)
        return 4;

      break;

    case TERRE:

      if (sd_at->attaque_1.type_attaque == FEU && sd_at->attaque_1.mode_attaque)
        return 1;

      if (sd_at->attaque_2.type_attaque == FEU && sd_at->attaque_2.mode_attaque)
        return 2;

      if (sd_at->attaque_3.type_attaque == FEU && sd_at->attaque_3.mode_attaque)
        return 3;

      if (sd_at->attaque_4.type_attaque == FEU && sd_at->attaque_4.mode_attaque)
        return 4;

      break;

    case AIR:

      if (sd_at->attaque_1.type_attaque == TERRE && sd_at->attaque_1.mode_attaque)
        return 1;

      if (sd_at->attaque_2.type_attaque == TERRE && sd_at->attaque_2.mode_attaque)
        return 2;

      if (sd_at->attaque_3.type_attaque == TERRE && sd_at->attaque_3.mode_attaque)
        return 3;

      if (sd_at->attaque_4.type_attaque == TERRE && sd_at->attaque_4.mode_attaque)
        return 4;

      break;

    case FEU:

      if (sd_at->attaque_1.type_attaque == EAU && sd_at->attaque_1.mode_attaque)
        return 1;

      if (sd_at->attaque_2.type_attaque == EAU && sd_at->attaque_2.mode_attaque)
        return 2;

      if (sd_at->attaque_3.type_attaque == EAU && sd_at->attaque_3.mode_attaque)
        return 3;

      if (sd_at->attaque_4.type_attaque == EAU && sd_at->attaque_4.mode_attaque)
        return 4;

      break;
    }
  }
  int rng = rand() % 4 +1;
  return rng;
}


/**
 * @brief retourne 1 si on capture le sdlon sinon retourne 0
 * 
*/
int capture(int lasso, int vie, int vieMax) { 
  float pourcentageVie = ((float) vie / (float) vieMax) * 100.0; // Calcul du pourcentage de vie 
  int rng = rand() % 101; // Génération d'un nombre aléatoire entre 0 et 100 
  rng -= pourcentageVie/2;
  if (lasso == 1 && rng < 5) { 
    printf("lasso 1 utilise\n");
    return 1; 
  }
  if (lasso == 2 && rng < 20) { 
    printf("lasso 2 utilise\n");
    return 1; 
  }
  if (lasso == 3 && rng < 75) {
    printf("lasso 3 utilise\n");
    return 1; 
  } 
  printf("\nOn ne reussit pas a capturer\n");
  return 0;
}
