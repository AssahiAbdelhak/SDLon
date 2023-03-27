#include "sdlon_generate.h"
#include "sdlon_init.h"
#include "player.h"
#define MAX_GAIN 1000

int sats(sdlon * sd_at, sdlon * sd_target, int num_at);
int ia(sdlon *sd_at, sdlon *sd_target);
int status_combat(player_t player, sdlon sd);
int can_fight(player_t player);
int get_xp(player_t *player);