#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "map.h"

#define HEIGHT 840
#define WIDTH 1280

void attaque(SDL_Window *window,SDL_Surface *screen,int width,int height,SDL_Surface *surface,int x,int y,char *name_attaque,int envir,int selected){
    SDL_Surface *attaque_surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 219, 233, 172);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    Uint32 bg = 0xdbeaa9;
    Uint32 bg_selected = 0x404040;
    //penser a ajouter d'autres couleurs qui change selon le type
    Uint32 bg_feu = 0xf3582c;
    Uint32 bg_normal = 0xabaf74;
    if(selected)
        SDL_FillRect(attaque_surface,NULL,bg);
    else
        SDL_FillRect(attaque_surface,NULL,bg_selected);
    SDL_Color black = {0,0,0};
    SDL_Color white = {255,255,255};
    SDL_Color red = {255,0,0};

    SDL_Surface *nom_attaque = TTF_RenderUTF8_Blended(font,"Flammèche",black);
    int fixed_height_for_type=30;
    int fixed_width_for_type=60;
    SDL_Surface *type = TTF_RenderUTF8_Blended(font,"Feu",white);
    
    SDL_Surface *type_container = SDL_CreateRGBSurface(0, fixed_width_for_type, fixed_height_for_type, 32, 0, 0, 0, 0);
    if(envir==0)
        SDL_FillRect(type_container,NULL,bg_feu);
    else if(envir==1)
        SDL_FillRect(type_container,NULL,bg_normal);
    SDL_Surface *force = TTF_RenderUTF8_Blended(font,"PP 20/25",black);

    SDL_Rect rect;
    rect.h=nom_attaque->h;
    rect.w=nom_attaque->w;
    rect.y=10;
    rect.x=(width-nom_attaque->w)/2;
    SDL_BlitSurface(nom_attaque,NULL,attaque_surface,&rect);
    rect.h=type->h;
    rect.w=type->w;
    rect.y=0;
    rect.x=(60-type->w)/2;
    SDL_BlitSurface(type,NULL,type_container,&rect);
    rect.h=fixed_height_for_type;
    rect.w=fixed_width_for_type;
    rect.y=50;
    rect.x=20;
    SDL_BlitSurface(type_container,NULL,attaque_surface,&rect);
    rect.h=force->h;
    rect.w=force->w;
    rect.y=50;
    rect.x=width-(force->w) - 10;
    SDL_BlitSurface(force,NULL,attaque_surface,&rect);
    rect.h=height;
    rect.w=width;
    rect.y=y;
    rect.x=x;
    SDL_BlitSurface(attaque_surface,NULL,surface,&rect);
    SDL_UpdateWindowSurface(window);
    return;
}

void handle_events(SDL_Window *window,SDL_Surface *screen,int nb){
    switch (nb){
    case 0:
        printControlles(window,screen);
        break;
    // à implémenter après
    default:
        break;
    }
    return;
}

void printSdlonBar(SDL_Window *window,SDL_Surface *screen,int width, int height){
    SDL_Surface *container = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    Uint32 blue_bg = 0x69bdef;
    SDL_FillRect(container,NULL,blue_bg);
    //Please resize it before use it
    SDL_Surface *img = IMG_Load("img/asset/SDLon_creature/(pinsir)-Pinchee.png");
    if(img==NULL){
        SDL_Log("ERRor");
        return ;
    }
    /*image*/
    SDL_Rect title_rect = {10,10,img->h,img->w};
    SDL_BlitSurface(img,NULL,container,&title_rect);
    SDL_Rect container_rect = {30,30,height,width};
    /*fin image*/
    /*nom de pokemon*/
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color white = {255,255,255};
    SDL_Surface *titre = TTF_RenderUTF8_Blended(font,"LATIOS",white);
    SDL_Rect nom_rect = {80,10,titre->h,titre->w};
    SDL_BlitSurface(titre,NULL,container,&nom_rect);
    /*fin de pokemon*/
    /*genre*/
    SDL_Surface *genre = TTF_RenderUTF8_Blended(font,"M",white);
    SDL_Rect genre_rect = {width - genre->w - 20,10,genre->h,genre->w};
    SDL_BlitSurface(genre,NULL,container,&genre_rect);
    /*fin genre*/
    /*hp*/
    SDL_Surface *niv_vie = TTF_RenderUTF8_Blended(font,"HP",white);
    SDL_Rect hp = { 80, 80, niv_vie->h, niv_vie->w };
    SDL_BlitSurface(niv_vie, NULL, container, &hp);
    int vie=90;
    SDL_Rect bar_vie = {120,85,200,20};
    SDL_Rect bar_vie_sdlon = {120,85,(vie*200)/100,20};
    SDL_FillRect(container,&bar_vie,SDL_MapRGB(container->format,214,248,228));  // 106,238,158
    SDL_FillRect(container,&bar_vie_sdlon,SDL_MapRGB(container->format,106,238,158));
    /*fin hp*/
    SDL_BlitSurface(container,NULL,screen,&container_rect);
    SDL_UpdateWindowSurface(window);
}

// max de n  est 4 je crois
void showAllSDlons(SDL_Window *window,SDL_Surface *screen,int n){
    Uint32 bg = 0x285171;
    SDL_FillRect(screen,NULL,bg);
    /*tittre*/
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color white = {255,255,255};
    SDL_Surface *titre = TTF_RenderUTF8_Blended(font,"Scene de Combat",white);
    SDL_Rect rect = {(WIDTH - titre->w)/2,10,titre->h,titre->w};
    SDL_BlitSurface(titre,NULL,screen,&rect);
    /*fin titre*/
    /*print sdlons*/
    printSdlonBar(window,screen,500,200);
    /*fin sdlons*/
    SDL_UpdateWindowSurface(window);
    int running =1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_QUIT:
                running = 0;
                return 0;
                break;
          }
        }
    }
}

void botton(SDL_Surface *surface,int width,int height,int selected){
    SDL_Surface *annuler_rect = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    Uint32 bg = 0x285171;
    Uint32 bg_selected = 0xdaed9c;
    if(selected)
        SDL_FillRect(annuler_rect,NULL,bg_selected);
    else
        SDL_FillRect(annuler_rect,NULL,bg);
    SDL_Color white = {255,255,255};
    SDL_Surface *annuler = TTF_RenderUTF8_Blended(font,"ANNULER",white);
    SDL_Rect rect;
    rect.h=annuler->h;
    rect.w=annuler->w;
    rect.y=(height - annuler->h)/2;
    rect.x=(width - annuler->w)/2;
    SDL_BlitSurface(annuler,NULL,annuler_rect,&rect);
    rect.h=height;
    rect.w=width;
    rect.y=200;
    rect.x=20;
    SDL_BlitSurface(annuler_rect,NULL,surface,&rect);
}

void drawAllOptions(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int width,int height,int selected){
    Uint32 border_color = 0xfbfbf9;
    SDL_FillRect(surface, NULL, border_color);

    attaque(window,screen,180,80,surface,10,10,"rien",0,(0==selected));
    attaque(window,screen,180,80,surface,210,10,"rien",0,(1==selected));
    attaque(window,screen,180,80,surface,10,110,"rien",0,(2==selected));
    attaque(window,screen,180,80,surface,210,110,"rien",0,(3==selected));
    botton(surface,width-40,40,(4==selected));
    /*botton d'annuler*/
    
    /*FIN*/
    SDL_Rect pos = { WIDTH-width-20, 560, width, height };
    SDL_BlitSurface(surface, NULL, screen, &pos);
    SDL_UpdateWindowSurface(window);
}

void handle_option_events(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int width,int height,int n){
    switch(n){
        case 0:
            onAttack(window,screen,surface,width,height);
            break;
        case 2:
            showAllSDlons(window,screen,4);
            break;
        case 3:
            printMap(window,screen);
            break;
        default:
            break;
    }
}

void onAttack(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int width,int height){
    int nb=0;
    drawAllOptions(window,screen,surface,width,height,nb);
    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_QUIT:
                running = 0;
                return 0;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        nb=(nb-2)%5;
                        break;
                    case SDLK_DOWN:
                        nb=(nb+2)%5;
                        break;
                    case SDLK_LEFT:
                        nb=(nb-1)%5;
                        if(nb<0)
                            nb += 5;
                        break;
                    case SDLK_RIGHT:
                        nb=(nb+1)%5;
                        break;
                    case SDLK_RETURN:
                        return handle_events(window,screen,nb);
                        break;
                }
                drawAllOptions(window,screen,surface,width,height,nb);
                break;
          }
        }
    }
    return ;
}

void updateOptions(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int n,int width,int height){
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
        attack = TTF_RenderUTF8_Blended(font,"Attaque",red);
        break;
    case 1:
        sac = TTF_RenderUTF8_Blended(font,"Sac",red);
        break;
    case 2:
        sdlon = TTF_RenderUTF8_Blended(font,"SDLon",red);
        break;
    case 3:
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
    rect.x = width-sac->w-10;
    rect.y=10;
    rect.h=sac->h;
    rect.w=sac->w;
    SDL_BlitSurface(sac,NULL,surface,&rect);
    rect.x = 10;
    rect.y=height-sdlon->h-10;
    rect.h=sdlon->h;
    rect.w=sdlon->w;
    SDL_BlitSurface(sdlon,NULL,surface,&rect);
    rect.x = width-fuite->w-10;
    rect.y= height-fuite->h - 10;
    rect.h=fuite->h;
    rect.w=fuite->w;
    SDL_BlitSurface(fuite,NULL,surface,&rect);
    SDL_Rect pos = { WIDTH-width-20, 560, width, height };
    SDL_BlitSurface(surface, NULL, screen, &pos);
    SDL_UpdateWindowSurface(window);
}

void printControlles(SDL_Window *window,SDL_Surface * screen){
     
    // Create a surface for the rectangle border
    int width = 400;
    int height = 250;
    SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    // intialisation
    
    //options
    int nb=0;
    updateOptions(window,screen,surface,nb,width,height);
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
                    case SDLK_RETURN:
                        handle_option_events(window,screen,surface,width,height,nb);
                        break;
                }
                updateOptions(window,screen,surface,nb,width,height);
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

    printPokemon(window,screen,"img/asset/SDLon_creature/face-animal.png",WIDTH-200,200);
    printPokemon(window,screen,"img/asset/SDLon_creature/dos-animal.png",0,HEIGHT-200);

    printPlayerStats(window,screen,"nom sdlon 1",20,30,15,50);
    printPlayerStats(window,screen,"nom sdlon 2",WIDTH-320,450,15,90);

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