#include "combat.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Si vie en mois, on heal
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
 * Calcul le nombre de degat 
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

int sats(sdlon * sd_at, sdlon * sd_target, int num_at){

    attaque at;
    int type_at, mode_at, degat_at, degat_current, status;

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
        if(mode_at == 0){
            if(!heal(sd_at, degat_at)){
                return 2;
            }
        }else{
            degat_current = conf_dgt(degat_at, type_at, sd_target->type);
            if(apply_attaque(sd_target, degat_current)){
                return 1;
            }else{
                return 0;
            }
        }
}