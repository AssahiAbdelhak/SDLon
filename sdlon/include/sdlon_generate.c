#include "sdlon_generate.h"
#include "level_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

sdlon generate_sdlon(int environement, int min_level, int max_level){

    //initialisation fonction random
    srand(time(NULL));

    //initialisation des variables
    int type_sd=(rand()%PROB);
    int level;
    int i=0;
    sdlon gen_sd;

    /**
     * environnement terrestre
     * type eau : impossible
     * type terre : 40%
     * type air : 40%
     * type feu : 20%
    */
    if(environement == 0){
        if(type_sd<=40){
            while(sdlon_s[i].type!=1 && sdlon_s[i].level >= min_level && i<rand()%100){
                i++;
            }
        }else if(type_sd>40&&type_sd<=80){
            while(sdlon_s[i].type!=2 && sdlon_s[i].level >= min_level && i<rand()%100){
                i++;
            }
        }else{
            while(sdlon_s[i].type!=0 && sdlon_s[i].level >= min_level && i<rand()%100){
                i++;
            }
        }
        if(sdlon_s[i].evolution==0){
            level = gen_level(sdlon_s[i].level, max_level);
        }else{
            level = gen_level(sdlon_s[i].level, sdlon_s[sdlon_s->evolution].level);
        }
        gen_sd.attaque_1 = sdlon_s[i].attaque_1;
        gen_sd.attaque_2 = sdlon_s[i].attaque_2;
        gen_sd.attaque_3 = sdlon_s[i].attaque_3;
        gen_sd.attaque_4 = sdlon_s[i].attaque_4;
        gen_sd.evolution = sdlon_s[i].evolution;
        gen_sd.type = sdlon_s[i].type;
        gen_sd.vie = sdlon_s[i].vie+gen_life(level);
        gen_sd.level = level;
        strcpy(gen_sd.nom, sdlon_s[i].nom);
        
    }
    return(gen_sd);
}