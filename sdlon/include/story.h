#ifndef NB_TOWN

#include "sdlon_init.h"
#include "player.h"

#define NB_TOWN;

typedef struct town_s{
    char * name;
    int badge_required;
    int environnement;
}town_t;

#ifndef