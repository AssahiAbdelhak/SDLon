# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>

/* VARIABLE CONSTANTE */
#define WIDTH 1280
#define HEIGHT 840
#define DELAY 3000
#define true 1
#define false 0
#define MARGE 100
#define LIGNE1 700
#define LIGNE2 750

float taille_x(int x);
float taille_y(int y);
void blackscreen(SDL_Surface * screen);
void print_image(SDL_Surface * screen, char * img, int xi, int yi, int hi, int wi);
void print_text(SDL_Surface * screen, const char * fontName, const char * texte, const int xt, const int yt, const int r, const int g, const int b);
void affichage(SDL_Window * window);
void PrintKeyInfo(SDL_KeyboardEvent * key);