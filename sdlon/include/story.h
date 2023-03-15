#ifndef NB_TOWN

#include "sdlon_init.h"
#include "player.h"
#include "item.h"

#define NB_TOWN 4
#define MAX_LAYER 50
#define MAX_TILES 5000
#define VILLE 0
#define ROUTE 1
#define MAISON 3
#define TILES_SIZE 16

<<<<<<< HEAD
#define NB_TOWN 4
=======
>>>>>>> c7de127e4d457d420c754ed8c38cf4be8f8fab8c

typedef struct town_s{
    char * name;
    int badge_required;
    int type_map;
    int environnement;
    int nb_layer;
    int nb_tiles;
    int tile_width;
    int tile_height;
    int first_grid;
    char * source_grid;
    int layer[MAX_LAYER][MAX_TILES];
}town_t;

<<<<<<< HEAD
=======
extern town_t all_town[NB_TOWN];
void town_init();
void display_town(town_t town);

>>>>>>> c7de127e4d457d420c754ed8c38cf4be8f8fab8c
#endif