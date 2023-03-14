#include "story.h"
#include <stdio.h>
#include <stdlib.h>

//gestion des pnj
//gestion de l'histoire du jeu
//gestion de la map en elle même

void town_init(){

}

/**
 * Vérifie que l'on peu aller dans la ville suivante
 * En ayant complété l'histoire du jeu
 * dans la ville actuelle
 * Passage dans la ville suivante nécéssite l'obtention du badge
*/
int can_next_town(player_t player, town_t town){
    return(town.badge_required<=player.badges);
}

int get_town_environnement(town_t town){
    return town.environnement;
}