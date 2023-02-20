#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int gen_level(int min_level, int max_level, int evol_sys){

    srand(time(NULL));
    int evol_pos=evol_sys%10, evol_tot=(evol_sys/10)%10;

    /*if (evol_pos=1 && evol_tot>1 && max_level>17){
        max_level = 17;
    }else if(evol_pos=2 && evol_tot>2 && max_level>39){
        max_level=39;
    }*/

    int dephasage = max_level-min_level;
    int level = (rand()%dephasage)+min_level+1;

    return (level);
}

int gen_life(int level){
    return (level*2);
}