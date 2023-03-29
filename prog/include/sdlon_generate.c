/**
* @file sdlon_generate.c
* Fichier de generation des sdlons 
* @author Wandrille Ballereau
* @author Abdelhak Assahi
* @author Lilian Colla
* @author Mohamed Besbes
* @date 2023
* @version 1.0 Alpha
*
*/
#include "sdlon_generate.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/**
 * @brief génère un niveau aléatoire
 * en fonction d'une borne min et max
*/
int gen_level(int min, int max){
    int dephasage = max-min;
    if(dephasage==0){
        dephasage = 1;
    }
    int lvl = min + (rand()%dephasage);
    return lvl;
}

/**
 * @brief génère la vie du sdlon
 * en fonction de son niveau
 * et de ses spécifications
*/
int gen_life(int level, int vie){
    return level*2+vie;
}

/**
 * @brief corrige les bornes min inutilisables
*/
int correctif(int min){
    switch (min)
    {
    case 16:
        return(15);
        break;

    case 38:
        return(37);
        break;
    
    default:
        return(min);
        break;
    }
}

/**
 * @brief Vérifie si le sdlon courant est utilisable ou non
*/
int is_usable(sdlon sd, int min, int max){
    if(sd.level <= max && sd.level >= min){
        return TRUE;
    }else if(sd.evolution != 0 && sdlon_s[sd.evolution].level > min && sd.level < min){
        return TRUE;
    }else if(sd.evolution == 0 && sd.level <= min){
        return TRUE;
    }else{
        return FALSE;
    }

}

/**
 * @brief génération du sdlon 
 * assigne les stats en fonction des spéc
*/
sdlon assign_sd(int i, int min, int max){

    sdlon gen_sd;
    int level = gen_level(min, max);

    gen_sd.attaque_1 = sdlon_s[i].attaque_1;
    gen_sd.attaque_2 = sdlon_s[i].attaque_2;
    gen_sd.attaque_3 = sdlon_s[i].attaque_3;
    gen_sd.attaque_4 = sdlon_s[i].attaque_4;
    gen_sd.evolution = sdlon_s[i].evolution;
    strcpy(gen_sd.back_face, sdlon_s[i].back_face);
    strcpy(gen_sd.front_face, sdlon_s[i].front_face);
    gen_sd.type = sdlon_s[i].type;
    gen_sd.vie_max = gen_life(level, sdlon_s[i].vie_max);
    gen_sd.vie = gen_sd.vie_max;
    gen_sd.level = level;
    gen_sd.xp = 0;
    strcpy(gen_sd.nom, sdlon_s[i].nom);

    return(gen_sd);
}

/**
 * @brief fonction principales de génération des sdlons
*/
sdlon generate_sdlon(int environement, int min_level, int max_level){

    //correctif des bornes inutilisables & init aléatoire
    min_level = correctif(min_level);
    srand(time(NULL));

    //déclaration des variables
    int find_sd = FALSE;
    int seed = (rand()%PROB)+1;
    int i = (rand()%NB_SDLON);
    sdlon gen_sd;

    /**
     * Environnement terrestre
     * type terre: 40%
     * type air: 40%
     * type feu 20%
     * type eau: 0%
    */
    if (environement == EAU){

        //type terre
        if(seed<=40){
            while(!find_sd){
                if(sdlon_s[i].type==TERRE && is_usable(sdlon_s[i], min_level, max_level)){
                    find_sd = TRUE;
                }else{
                    i = (rand()%NB_SDLON);
                }
            }
        //type air
        }else if(seed > 40 && seed <= 60){
            while(!find_sd){
                if(sdlon_s[i].type==AIR && is_usable(sdlon_s[i], min_level, max_level)){
                    find_sd = TRUE;
                }else{
                    i = (rand()%NB_SDLON);
                }
            }
        //type feu
        }else{
            while(!find_sd){
                if(sdlon_s[i].type==FEU && is_usable(sdlon_s[i], min_level, max_level)){
                    find_sd = TRUE;
                }else{
                    i = (rand()%NB_SDLON);
                }
            }
        }
    /**
     * environnement aquatique
     * type eau: 85%
     * type air: 10%
     * type terre: 5%
    */
    }else if(environement==TERRE){

        //type terre
        if(seed<=5){
            while(!find_sd){
                if(sdlon_s[i].type==TERRE && is_usable(sdlon_s[i], min_level, max_level)){
                    find_sd = TRUE;
                }else{
                    i = (rand()%NB_SDLON);
                }
            }
        //type air
        }else if(seed > 5 && seed <= 15){
            while(!find_sd){
                if(sdlon_s[i].type==AIR && is_usable(sdlon_s[i], min_level, max_level)){
                    find_sd = TRUE;
                }else{
                    i = (rand()%NB_SDLON);
                }
            }
        //type eau
        }else{
            while(!find_sd){
                if(sdlon_s[i].type==EAU && is_usable(sdlon_s[i], min_level, max_level)){
                    find_sd = TRUE;
                }else{
                    i = (rand()%NB_SDLON);
                }
            }
        }
    /**
     * environnement volcanique
     * type feu: 70%
     * type air: 20%
     * type terre: 10%
     * type eau: 0%
    */
    }else if(environement==AIR){

        //type terre
        if(seed<=10){
            while(!find_sd){
                if(sdlon_s[i].type==TERRE && is_usable(sdlon_s[i], min_level, max_level)){
                    find_sd = TRUE;
                }else{
                    i = (rand()%NB_SDLON);
                }
            }
        //type air
        }else if(seed > 10 && seed <= 30){
            while(!find_sd){
                if(sdlon_s[i].type==AIR && is_usable(sdlon_s[i], min_level, max_level)){
                    find_sd = TRUE;
                }else{
                    i = (rand()%NB_SDLON);
                }
            }
        //type feu
        }else{
            while(!find_sd){
                if(sdlon_s[i].type==FEU && is_usable(sdlon_s[i], min_level, max_level)){
                    find_sd = TRUE;
                }else{
                    i = (rand()%NB_SDLON);
                }
            }
        }
    }

    /**
     * appel de la génération (assignation des stats) du sdlons
     * avec les données crée dans le script
     * (sdlon, vie, level)
    */
    if(sdlon_s[sdlon_s[i].evolution].level > max_level || sdlon_s[i].evolution == 0){
        if(sdlon_s[i].level > min_level){
            gen_sd=assign_sd(i, sdlon_s[i].level, max_level);
        }else{
            gen_sd=assign_sd(i, min_level, max_level);
        }
    }else{
        if(sdlon_s[i].level > min_level){
            gen_sd=assign_sd(i, sdlon_s[i].level, sdlon_s[sdlon_s[i].evolution].level-1);
        }else{
            gen_sd=assign_sd(i, min_level, sdlon_s[sdlon_s[i].evolution].level-1);
        }
        
    }
    
    return(gen_sd);
}