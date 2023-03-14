#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "map.h"

#define HEIGHT 840
#define WIDTH 1280

void updateOptions(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int n){
    Uint32 border_color = 0xf8f8d8;
    SDL_FillRect(surface, NULL, border_color);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color black = {0,0,0};
    SDL_Color red = {255,0,0};

    SDL_Surface *attack = TTF_RenderUTF8_Blended(font,"Attaque",black);
    SDL_Surface *sac = TTF_RenderUTF8_Blended(font,"Sac",black);
    SDL_Surface *sdlon = TTF_RenderUTF8_Blended(font,"SDLon",black);
    SDL_Surface *fuite = TTF_RenderUTF8_Blended(font,"Fuite",black);
    switch (n){
    case 0:
        SDL_Log("in switch %d\n",n);
        attack = TTF_RenderUTF8_Blended(font,"Attaque",red);
        break;
    case 1:
        SDL_Log("in switch %d\n",n);
        sac = TTF_RenderUTF8_Blended(font,"Sac",red);
        break;
    case 2:
        SDL_Log("in switch %d\n",n);
        sdlon = TTF_RenderUTF8_Blended(font,"SDLon",red);
        break;
    case 3:
        SDL_Log("in switch %d\n",n);
        fuite = TTF_RenderUTF8_Blended(font,"Fuite",red);
        break;
    
    default:
        break;
    }

    SDL_Rect rect;
    rect.x = 10;
    rect.y=10;
    rect.h=attack->h;
    rect.w=attack->w;
    SDL_BlitSurface(attack,NULL,surface,&rect);
    rect.x = 300-sac->w-10;
    rect.y=10;
    rect.h=sac->h;
    rect.w=sac->w;
    SDL_BlitSurface(sac,NULL,surface,&rect);
    rect.x = 10;
    rect.y=150-sdlon->h-10;
    rect.h=sdlon->h;
    rect.w=sdlon->w;
    SDL_BlitSurface(sdlon,NULL,surface,&rect);
    rect.x = 300-fuite->w-10;
    rect.y= 150-fuite->h - 10;
    rect.h=fuite->h;
    rect.w=fuite->w;
    SDL_BlitSurface(fuite,NULL,surface,&rect);
    SDL_Rect pos = { WIDTH-300-20, 560, 300, 150 };
    SDL_BlitSurface(surface, NULL, screen, &pos);
    SDL_UpdateWindowSurface(window);
}

void printControlles(SDL_Window *window,SDL_Surface * screen){
     
    // Create a surface for the rectangle border
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 300, 150, 32, 0, 0, 0, 0);
    // intialisation
    
    //options
    int nb=0;
    updateOptions(window,screen,surface,nb);
    // Update the screen
    SDL_UpdateWindowSurface(window);
    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_QUIT:
                SDL_DestroyWindow(window);
                SDL_Quit();
                running = 0;
                return 0;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        nb=(nb-2)%4;
                        break;
                    case SDLK_DOWN:
                        nb=(nb+2)%4;
                        break;
                    case SDLK_LEFT:
                        nb=(nb-1)%4;
                        if(nb<0)
                            nb += 4;
                        break;
                    case SDLK_RIGHT:
                        nb=(nb+1)%4;
                        break;
                }
                SDL_Log("%d\n",nb);
                updateOptions(window,screen,surface,nb);
                break;
          }
        }
    }
}

void printPlayerStats(SDL_Window *window,SDL_Surface * screen,char * nom,int x,int y, int niveau,int vie){
    Uint32 border_color = 0xf8f8d8;

    // Create a surface for the rectangle border
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 300, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, border_color);

    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color black = {0,0,0};
    SDL_Surface *sdlon_name = TTF_RenderUTF8_Blended(font,nom,black);
    SDL_Surface *sdlon_level = TTF_RenderUTF8_Blended(font,"N: 15",black);
    SDL_Surface *niv_vie = TTF_RenderUTF8_Blended(font,"HP",black);
    SDL_Rect nom_rect = { 10, 10, sdlon_name->h, sdlon_name->w };
    SDL_BlitSurface(sdlon_name, NULL, surface, &nom_rect);
    SDL_Rect level = { 300 - sdlon_level->w - 20, 10, sdlon_name->h, sdlon_name->w };
    SDL_BlitSurface(sdlon_level, NULL, surface, &level);
    
    SDL_Rect hp = { 10, 65, niv_vie->h, niv_vie->w };
    SDL_BlitSurface(niv_vie, NULL, surface, &hp);

    SDL_Rect bar_vie = {60,70,200,20};
    SDL_Rect bar_vie_sdlon = {60,70,(vie*200)/100,20};
    SDL_FillRect(surface,&bar_vie,SDL_MapRGB(surface->format,214,248,228));  // 106,238,158
    SDL_FillRect(surface,&bar_vie_sdlon,SDL_MapRGB(surface->format,106,238,158));

    SDL_Rect pos = { x, y, 300, 100 };
    SDL_BlitSurface(surface, NULL, screen, &pos);
    // Update the screen
    SDL_UpdateWindowSurface(window);
}

void printPokemon(SDL_Window *window,SDL_Surface * screen,char *nom_fichier,int x,int y){
    SDL_Surface *pokemon = IMG_Load(nom_fichier);
    SDL_Rect dest;
    dest.h = pokemon->h;
    dest.w = pokemon->w;
    dest.x = x;
    dest.y = y;
    SDL_BlitSurface(pokemon,NULL,screen,&dest);
    SDL_UpdateWindowSurface(window);
}
int afficherLeCombat(SDL_Window *window,SDL_Surface * screen){
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    /*Afficher la map*/
    printLayer(window,screen,combat_sol,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,combat_ciel,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,combat_arbre,"images/pokemon_style.png",1,16,16);

    printPokemon(window,screen,"img/asset/face-animal.png",WIDTH-200,200);
    printPokemon(window,screen,"img/asset/dos-animal.png",0,HEIGHT-200);

    printPlayerStats(window,screen,"nom sdlon 1",20,30,15,50);
    printPlayerStats(window,screen,"nom sdlon 2",WIDTH-320,450,15,50);

    printControlles(window,screen);
    return;
    // int running = 1;
    // while (running) {
    //     SDL_Event e;
    //     while (SDL_PollEvent( & e)) {
    //       switch (e.type) {
    //         case SDL_QUIT:
    //             SDL_DestroyWindow(window);
    //             SDL_Quit();
    //             running = 0;
    //             return 0;
    //             break;
    //       }
    //     }
    // }
}