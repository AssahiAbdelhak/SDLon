#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.h"


void waiting(Uint32 *start_time);
void movePlayer(SDL_Window *widow,SDL_Surface *spirit,SDL_Surface *screen,SDL_Surface *copy,SDL_Rect pre_rect,SDL_Rect rect,enum directions dir,enum actions act,Uint32 *start_time);
void destroy(SDL_Window *pWindow,SDL_Surface *surface);
void printLayer(SDL_Window *window,SDL_Surface * screen,int tiles[4160],char * nom_fichier,int firstgid, int tile_width,int tile_height);
int localisationValide(int x,int y);
void printSpirit(SDL_Window *widow,SDL_Surface * screen,char *nom_fichier,int x,int y,SDL_Surface *hintSliceFromMap,SDL_Surface *hint);
void printMap(SDL_Window *window,SDL_Surface * screen);
int detecterBuissons(SDL_Window * window, SDL_Surface * screen,int x,int y,SDL_Surface *hintSliceFromMap,SDL_Surface *hint);
