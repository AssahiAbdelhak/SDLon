/**
* @file IA_Combat.c
* @author Wandrille Ballereau
* @author Abdelhak Assahi
* @author Lilian Colla
* @author Mohamed Besbes
* @date 2023
* @version 1.0 Alpha
*
*/

#include "include/sdlon_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ia_Combat(sdlon * sd_at, sdlon * sd_target){
/**
* @brief Retourne l'attaque à effectuer pour le sdlon adverse
*/
    
    float pv; //pourcentage de vie 
    pv = (sd_at->vie / sd_at->vie_max) * 100;
    int chance = (rand()%100);

    //choix d'une attaque si un oneshot est possible
    if((sd_at->attaque_1.degat >= sd_target->vie)&& sd_at->mode_attaque && chance >= 25){ //75% de chance
        return 1;
    }
    if((sd_at->attaque_2.degat >= sd_target->vie)&& sd_at->mode_attaque && chance >= 25){
        return 2;
    }
    if((sd_at->attaque_3.degat >= sd_target->vie)&& sd_at->mode_attaque && chance >= 25){
        return 3;
    }
    if((sd_at->attaque_4.degat >= sd_target->vie)&& sd_at->mode_attaque && chance >= 25){
        return 4;
    }

    if(/*pv <= 10 && chance >= 45*/ chance >= pv){ // si un SDLon a moins de 10% de vie il se heal
        if(sd_at->attaque_1.mode_attaque == 0){
            return 1;
        }
        if(sd_at->attaque_2.mode_attaque == 0){
            return 2;
        }
        if(sd_at->attaque_3.mode_attaque == 0){
            return 3;
        }
        if(sd_at->attaque_4.mode_attaque == 0){
            return 4;
        }
    }else{
        switch(sd_target->type){//choix de l'attaque la plus optimiser
            case 0:
                if(sd_at->attaque_1.type_attaque == 2 && sd_at->mode_attaque) return 1;
                if(sd_at->attaque_2.type_attaque == 2 && sd_at->mode_attaque) return 2;
                if(sd_at->attaque_3.type_attaque == 2 && sd_at->mode_attaque) return 3;
                if(sd_at->attaque_4.type_attaque == 2 && sd_at->mode_attaque) return 4;
                break;
            case 1:
                if(sd_at->attaque_1.type_attaque == 3 && sd_at->mode_attaque) return 1;
                if(sd_at->attaque_2.type_attaque == 3 && sd_at->mode_attaque) return 2;
                if(sd_at->attaque_3.type_attaque == 3 && sd_at->mode_attaque) return 3;
                if(sd_at->attaque_4.type_attaque == 3 && sd_at->mode_attaque) return 4;
                break;
            case 2:
                if(sd_at->attaque_1.type_attaque == 1 && sd_at->mode_attaque) return 1;
                if(sd_at->attaque_2.type_attaque == 1 && sd_at->mode_attaque) return 2;
                if(sd_at->attaque_3.type_attaque == 1 && sd_at->mode_attaque) return 3;
                if(sd_at->attaque_4.type_attaque == 1 && sd_at->mode_attaque) return 4;
                break;
            case 3:
                if(sd_at->attaque_1.type_attaque == 0 && sd_at->mode_attaque) return 1;
                if(sd_at->attaque_2.type_attaque == 0 && sd_at->mode_attaque) return 2;
                if(sd_at->attaque_3.type_attaque == 0 && sd_at->mode_attaque) return 3;
                if(sd_at->attaque_4.type_attaque == 0 && sd_at->mode_attaque) return 4;
                break;
        }
    }


}

