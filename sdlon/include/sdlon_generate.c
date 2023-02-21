#include "sdlon_generate.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*int last_evol(int evol_sys){
    int evol_pos=evol_sys%10, evol_tot=(evol_sys/10)%10;
    return(evol_pos==evol_tot);
}

int gen_level(int min_level, int max_level, int evol_sys){

    srand(time(NULL));
    int evol_pos=evol_sys%10, evol_tot=(evol_sys/10)%10;

    int dephasage = max_level-min_level;
    printf("depf: %d, min: %d, max: %d", dephasage, min_level, max_level);
    int level = (rand()%dephasage)+min_level+1;

    if (evol_pos==1 && evol_tot>1 && level>17){
        level = 17;
    }else if(evol_pos==2 && evol_tot>2 && level>39){
        level=39;
    }

    return (level);
}

int gen_life(int level){
    return (level*2);
}

sdlon generate_sdlon(int environement, int min_level, int max_level){

    //initialisation fonction random
    srand(time(NULL));

    //initialisation des variables
    int type_sd=(rand()%PROB);
    int seed=(rand()%NB_SDLON)*(rand()%100)+1;
    int level;
    int i=0, it=0;
    int current_gen = 0;
    sdlon gen_sd;
    printf("coucou\n");

    /**
     * environnement terrestre
     * type eau : impossible
     * type terre : 40%
     * type air : 40%
     * type feu : 20%
    */
    /*if(environement == 0){

        if(type_sd<=40){
            printf("coucou\n");
            while(!current_gen){
                printf("%s\n", sdlon_s[i].nom);
                if(sdlon_s[i].type==1 && 
                sdlon_s[i].level >= min_level && 
                (sdlon_s[i].level <= max_level || last_evol(sdlon_s[i].evol_sys) )
                && it>seed){
                    current_gen=1;
                }else{
                    i++;
                    it++;
                    if(i>=NB_SDLON){
                        i=0;
                    }
                }

            }
        }else if(type_sd>40&&type_sd<=80){
printf("coucou\n");
            while(!current_gen){printf("%s\n", sdlon_s[i].nom);
                if(sdlon_s[i].type==2 && 
                sdlon_s[i].level >= min_level  && 
                (sdlon_s[i].level <= max_level || last_evol(sdlon_s[i].evol_sys)) && 
                it>seed){
                    current_gen=1;
                }else{
                    i++;
                    it++;
                    if(i>=NB_SDLON){
                        i=0;
                    }
                }

            }
        }else{
printf("coucou\n");
            while(!current_gen){printf("%s\n", sdlon_s[i].nom);
                if(sdlon_s[i].type==0 && 
                sdlon_s[i].level >= min_level 
                && (sdlon_s[i].level <= max_level || last_evol(sdlon_s[i].evol_sys))
                && it>seed){
                    current_gen=1;
                }else{
                    i++;
                    it++;
                    if(i>=NB_SDLON){
                        i=0;
                    }
                }
            }

        }
    }

    /**
     * environnement aquatique
     * type eau : 60%
     * type terre : 10%
     * type air : 30%
     * type feu : 0%
    */
    /*if(environement == 1){

        if(type_sd<=60){

            while(!current_gen){
                if(sdlon_s[i].type==-1 && 
                (sdlon_s[i].level >= min_level || last_evol(sdlon_s[i].evol_sys) ) && 
                sdlon_s[i].level <= max_level
                && it>seed){
                    current_gen=1;
                }else{
                    i++;
                    it++;
                    if(i>=NB_SDLON){
                        i=0;
                    }
                }

            }
        }else if(type_sd>60&&type_sd<=90){

            while(!current_gen){
                if(sdlon_s[i].type==2 && 
                (sdlon_s[i].level >= min_level || last_evol(sdlon_s[i].evol_sys)) && 
                sdlon_s[i].level <= max_level && 
                it>seed){
                    current_gen=1;
                }else{
                    i++;
                    it++;
                    if(i>=NB_SDLON){
                        i=0;
                    }
                }

            }
        }else{

            while(!current_gen){
                if(sdlon_s[i].type==1 && 
                (sdlon_s[i].level >= min_level || last_evol(sdlon_s[i].evol_sys))
                && sdlon_s[i].level <= max_level 
                && it>seed){
                    current_gen=1;
                }else{
                    i++;
                    it++;
                    if(i>=NB_SDLON){
                        i=0;
                    }
                }
            }

        }
        
    }*/

    /*level = gen_level(sdlon_s[i].level, max_level, sdlon_s[i].evol_sys);

    gen_sd.attaque_1 = sdlon_s[i].attaque_1;
    gen_sd.attaque_2 = sdlon_s[i].attaque_2;
    gen_sd.attaque_3 = sdlon_s[i].attaque_3;
    gen_sd.attaque_4 = sdlon_s[i].attaque_4;
    gen_sd.evolution = sdlon_s[i].evolution;
    gen_sd.type = sdlon_s[i].type;
    gen_sd.vie = sdlon_s[i].vie+gen_life(level);
    gen_sd.level = level;
    strcpy(gen_sd.nom, sdlon_s[i].nom);
    
    return(gen_sd);
}*/

int gen_level(int min, int max){
    printf("%d, %d\n", min, max);
    int dephasage = max-min;
    int lvl = min + (rand()%dephasage);
    return lvl;
}

int gen_life(int level, int vie){
    return level*2+vie;
}

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

sdlon assign_sd(int i, int min, int max){

    sdlon gen_sd;
    int level = gen_level(min, max);

    gen_sd.attaque_1 = sdlon_s[i].attaque_1;
    gen_sd.attaque_2 = sdlon_s[i].attaque_2;
    gen_sd.attaque_3 = sdlon_s[i].attaque_3;
    gen_sd.attaque_4 = sdlon_s[i].attaque_4;
    gen_sd.evolution = sdlon_s[i].evolution;
    gen_sd.type = sdlon_s[i].type;
    gen_sd.vie = gen_life(level, sdlon_s[i].vie);
    gen_sd.level = level;
    strcpy(gen_sd.nom, sdlon_s[i].nom);

    return(gen_sd);
}

sdlon generate_sdlon(int environement, int min_level, int max_level){

    min_level = correctif(min_level);

    srand(time(NULL));

    int find_sd = FALSE;
    int seed = rand()%PROB;
    int i = (rand()%NB_SDLON);
    int level;
    sdlon gen_sd;

    if (environement == 0){
        while(!find_sd){
            if(sdlon_s[i].type==0 && is_usable(sdlon_s[i], min_level, max_level)){
                    find_sd = TRUE;
                }else{
                    i = (rand()%NB_SDLON);
                }
        }
    }

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