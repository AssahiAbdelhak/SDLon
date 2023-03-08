#include "sdlon_init.h"

#ifndef HOMME
/**
 * Definition des macros
*/
#define HOMME 0
#define FEMME 1
#define MAIN_MAX 6

/**
 * structure du joueur
 * prenom, genre, sdlons courrant
*/
typedef struct player_s{
    char * name;
    int genre;
    int nb_current_sdlon;
    sdlon sd[6];
}player_t;

player_t player_create(char * name, int genre);
player_t player_init(char * name_file);
#endif