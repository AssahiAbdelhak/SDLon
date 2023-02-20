#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int gen_level(int min_level, int max_level){
    srand(time(NULL));
    return ((rand()%max_level)+min_level+1);
}

int gen_life(int level){
    return (level*2);
}