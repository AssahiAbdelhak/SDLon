#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "map.h"
#include "include/sdlon_generate.h"
#include "include/sdlon_init.h"
#include "combat.h"
#include <time.h>
#define TILE_SIZE 32
#define WIDTH 1280
#define HEIGHT 832
#define frameTime 100

enum directions{DOWN,LEFT,RIGHT,UP};
enum actions{DEF1,WALK1,DEF2,WALK2};

/*------------------------------Variable globales-------------------------------------*/

SDL_Rect hintBox,hintContainer;
SDL_Surface *pasSdlon;
int dansLesBuissons=0;

//town_init();

void waiting(Uint32 *start_time){
    *start_time = SDL_GetTicks();
    Uint32 elapsed_time = SDL_GetTicks() - *start_time;
    if (elapsed_time < frameTime){
        SDL_Delay(frameTime - elapsed_time);
    }
    // Update the start time for the next frame
    *start_time = SDL_GetTicks();
}

void movePlayer(SDL_Window *window,SDL_Surface *spirit,SDL_Surface *screen,SDL_Surface *copy,SDL_Rect pre_rect,SDL_Rect rect,enum directions dir,enum actions act,Uint32 *start_time){
    
    SDL_BlitSurface(copy,NULL,screen,&pre_rect);
    SDL_Rect copy_rect = {0,0,32,32};
    SDL_BlitSurface(screen,&rect,copy,&copy_rect);
    SDL_Rect src_rect = {0,0,32,32};
    src_rect.y = dir*32;
    src_rect.x = act*32;
    SDL_BlitSurface(spirit,&src_rect,screen,&rect);
    SDL_UpdateWindowSurface(window);
    waiting(start_time);
    act = (act+2)%4;
    src_rect.x = act*32;
    SDL_BlitSurface(spirit,&src_rect,screen,&rect);
    SDL_UpdateWindowSurface(window);
    
}


void destroy(SDL_Window *pWindow,SDL_Surface *surface){
    SDL_FreeSurface(surface);
  SDL_DestroyWindow(pWindow);
    SDL_Quit();
    exit(1);
}

void printLayer(SDL_Window *window,SDL_Surface * screen,int tiles[4160],char * nom_fichier,int firstgid, int tile_width,int tile_height){
    SDL_Surface * tile = IMG_Load(nom_fichier);
    if(tile==NULL)
        SDL_Log("NULL!!!!\n");
    SDL_Rect rect = {0,0,tile_width,tile_height};
    int tile_x;
    int tile_y;
    SDL_Rect src_rect;
    src_rect.h=16;
    src_rect.w=16;
    for(int i = 0 ;i < 52 ; i++){
        for(int j = 0 ;j < 80 ; j++){
            if(tiles[i*80+j]==0){
                continue;
            }
            tile_x = ((tiles[i*80+j]-1)/tile_height);
            tile_y = ((tiles[i*80+j]-1)%tile_width);
            src_rect.x = tile_y * tile_height;
            src_rect.y = tile_x * tile_width;
            rect.x = tile_width*j;
            rect.y = tile_height*i;
            SDL_BlitSurface(tile,&src_rect,screen,&rect);
        }
    }
    SDL_Log("layer Done!!\n");
    SDL_FreeSurface(tile);
    SDL_UpdateWindowSurface(window);
    
}

int localisationValide(int x,int y){
    if(x<0||x>WIDTH-32||y<0||y>HEIGHT-32)
        return 0;
    if(collision[(y/16)*80+(x/16)])
        return 0;
    return 1;
}

void printSpirit(SDL_Window *window,SDL_Surface * screen,char *nom_fichier,int x,int y,SDL_Surface *hintSliceFromMap,SDL_Surface *hint,player_t player){
    SDL_Surface * spirit = IMG_Load(nom_fichier);
    printf("image good");
    SDL_Rect rect = {x,y,32,32};
    SDL_Rect copy_rect = {0,0,32,32};
    
    enum directions dir = DOWN;
    enum actions act = DEF1;
// prq 32 et pas 16 pcq on veut recuperer les 4 part du personnage
    SDL_Rect src_rect = {dir*16,act*16,32,32};
    SDL_Surface* copy = SDL_CreateRGBSurface(0, 32, 32, screen->format->BitsPerPixel, 0, 0, 0, 0);
    if(SDL_BlitSurface(screen,&rect,copy,&copy_rect)<0)
        printf("erreur 1\n");
    if(SDL_BlitSurface(spirit,&src_rect,screen,&rect)<0)
        printf("erreur 2\n");
    SDL_UpdateWindowSurface(window);
    int running = 1;
    int move = 0;
    Uint32 start_time = SDL_GetTicks(); // 100 milliseconds per frame
    printf("goo!!!");
      while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
            move = 0;
          switch (e.type) {
            case SDL_QUIT:
                destroy(window,screen);
                running = 0;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    
                    case SDLK_UP:
                        if(localisationValide(x,y-16)){
                            move = 1;
                            dir = UP;
                            
                        }
                        break;
                    case SDLK_DOWN:
                        if(localisationValide(x,y+16)){
                            move = 1;
                            dir = DOWN;
                            
                        }
                        break;
                    case SDLK_LEFT:
                        if(localisationValide(x-16,y)){
                            move = 1;
                            dir = LEFT;
                            
                        }
                        break;
                    case SDLK_RIGHT:
                        if(localisationValide(x+16,y)){
                            move = 1;
                            dir = RIGHT;
                            
                        }
                        break;
                    case SDLK_e:
                        move=0;
                        if(dansLesBuissons){
                            SDL_Log("E cliqué\n");
                            //return afficherLeCombat(window,screen);
                            //sdlon sdl1 = generate_sdlon(0,5,20);
                            //SDL_Log("nom == %s\n",sdl1.nom);
                            //decouvrirLeSdlon();
                            int seed = rand()%100;
                            printf("%d\n",seed);
                            
                            if(seed<=10){
                                afficherLeCombat(window,screen,player);

                            }else{
                                SDL_BlitSurface(hintSliceFromMap,&hintContainer,screen,&hintBox);
        SDL_UpdateWindowSurface(window);
                                SDL_BlitSurface(pasSdlon,&hintContainer,screen,&hintBox);
                                SDL_UpdateWindowSurface(window);
                            }
                        }
                        break;
                    case SDLK_ESCAPE: ;
                        printf("escape clicked\n");
                        TTF_Font *police = TTF_OpenFont("OpenSans-Bold.ttf", 20);
                        char *menus[4] = {"Nouvelle Partie","Charger Partie","Charger Patch","Quitter"};
                        afficherMenu(window,screen,menus,4,police);
                        return;
                        break;
                    default:
                        move=0;
                        break;
                }
                
                dansLesBuissons = detecterBuissons(window,screen,x+16,y+16,hintSliceFromMap,hint);
                break;
            case SDL_MOUSEMOTION:
                break;
            }
               
        }
        if(move){
            if(dir==UP){
                SDL_Rect nouv_rect = {rect.x,rect.y-16,rect.h,rect.w};
                            movePlayer(window,spirit,screen,copy,rect,nouv_rect,UP,WALK1,&start_time);
                            rect.y = nouv_rect.y;
                            y=y-16;
                            player.y=y;
                    }
                    if(dir==DOWN){
                        SDL_Rect nouv_rect = {rect.x,rect.y+16,rect.h,rect.w};
                            movePlayer(window,spirit,screen,copy,rect,nouv_rect,DOWN,WALK1,&start_time);
                            rect.y = nouv_rect.y;
                            y=y+16;
                            player.y=y;
                    }
                    if(dir==LEFT){
                        SDL_Rect nouv_rect = {rect.x-16,rect.y,rect.h,rect.w};
                            movePlayer(window,spirit,screen,copy,rect,nouv_rect,LEFT,WALK1,&start_time);
                            rect.x = nouv_rect.x;
                            x=x-16;
                            player.x=x;
                    }
                    if(dir==RIGHT){
                        SDL_Rect nouv_rect = {rect.x+16,rect.y,rect.h,rect.w};
                            movePlayer(window,spirit,screen,copy,rect,nouv_rect,RIGHT,WALK1,&start_time);
                            rect.x = nouv_rect.x;
                            x=x+16;
                            player.x=x;
                    }
        } 
        if (SDL_GetTicks() - start_time > 2000){
                    Uint32 start_temps = SDL_GetTicks();
                    movePlayer(window,spirit,screen,copy,rect,rect,dir,DEF1,&start_temps);
                    movePlayer(window,spirit,screen,copy,rect,rect,dir,DEF2,&start_temps);
        }
    }
}

void printMap(SDL_Window *window,SDL_Surface * screen,player_t player){
    
    printLayer(window,screen,sol,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,chemin,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,arbre,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,buissons,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,objets,"images/pokemon_style.png",1,16,16);
    //***
    
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color white = {255,255,255};
    SDL_Surface *hint = TTF_RenderUTF8_Blended(font,"Cliquez sur E pour decouvrir le sdlon",white);
    pasSdlon = TTF_RenderUTF8_Blended(font,"Vous n'avez pas trouvez de sdlon",white);
    
    hintBox.y=HEIGHT - 100 - hint->h;
    hintBox.x=(WIDTH - hint->w)/2;
    hintBox.h=hint->h;
    hintBox.w=hint->w; 
    hintContainer.x=0;
    hintContainer.y=0;
    hintContainer.h=hint->h;
    hintContainer.w=hint->w;
    SDL_Surface *hintSliceFromMap = SDL_CreateRGBSurface(0, hint->w, hint->h, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_BlitSurface(screen,&hintBox,hintSliceFromMap,&hintContainer);
    ///***
    printf("print this\n");
    
    if(player.genre==HOMME)
        printSpirit(window,screen,"images/mec.png",player.x,player.y,hintSliceFromMap, hint,player);
    else
        printSpirit(window,screen,"images/meuf.png",player.x,player.y,hintSliceFromMap, hint,player);
    return ;
    int running = 1;
      while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_QUIT:
                running = 0;
                break;  
        }
      }
}}
int detecterBuissons(SDL_Window * window, SDL_Surface * screen,int x,int y,SDL_Surface *hintSliceFromMap,SDL_Surface *hint){
    
    if(buissons[(y/16)*80+(x/16)]){
        SDL_BlitSurface(hint,&hintContainer,screen,&hintBox);
        SDL_UpdateWindowSurface(window);
        return 1;
    }else{        
        SDL_BlitSurface(hintSliceFromMap,&hintContainer,screen,&hintBox);
        SDL_UpdateWindowSurface(window);
        return 0;
    }
}