void afficherLeCombat(SDL_Window *window,SDL_Surface * screen,player_t player);
int afficherTableauMenu(SDL_Window *window,SDL_Surface * screen,int width,int height);
int showAllSDlons(SDL_Window *window,SDL_Surface *screen,int n,player_t player);
void showSac(SDL_Window *window,SDL_Surface * screen,char * noms[],char * descs[],int n,player_t player, int (*f)(SDL_Window *window,SDL_Surface * screen,player_t player));