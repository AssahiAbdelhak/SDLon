#ifndef HOMME

#include "sdlon_init.h"
#include "item.h"

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
    int x;
    int y;
    int nb_current_sdlon;
    int badges;
    sdlon sd[6];
    inventory inventaire;
    int sd_in_use;
    int argent;
    int current_town;
    int story_position;
}player_t;

/*
    Definition de la box
*/

typedef struct box{
    sdlon current;
    struct box * next;
    struct box * precedent;
}box;
//box * boiteASdlon;

player_t player_create(char * name, int genre, char * file_name);
player_t player_init(char * file_name);
int player_quit(player_t * p);
int add_sdlon_in_set(sdlon sd, player_t * player);
int remove_sdlon_in_set(sdlon sd, player_t * player);
int switch_sdlon_from_set(sdlon sd_in, sdlon sd_out, player_t * player);
//int send_sdlon_in_box(sdlon sd);
//int load_box(char * name);
//int create_box();
int get_player_item(player_t * player, int num_item);
int add_items(int num_item, int qtt, player_t * player);
int remove_items(int num_item, int qtt, player_t * player);
extern int sspi(player_t player);
extern int display_pss(player_t player);
#endif