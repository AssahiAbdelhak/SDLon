#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "map.h"
#include "include/story.h"
#include "include/item.h"
#include "include/sdlon_generate.h"
#include "include/sdlon_init.h"
#include "include/combat.h"
#include "combat.h"
#include <time.h>
#define TILE_SIZE 32
#define WIDTH 1280
#define HEIGHT 832
#define frameTime 100
#define BUISSONS 1
#define PORTE 2
#define STORE 1
#define DAME 3
#define VIDE -1

enum directions{DOWN,LEFT,RIGHT,UP};
enum actions{DEF1,WALK1,DEF2,WALK2};


void afficherLaBoutique(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,player_t player,int x_map,int y_map){
    SDL_Surface * argent = SDL_CreateRGBSurface(0, 100, 50, surface->format->BitsPerPixel, 0, 255, 255, 255);
    char * argent_texte = malloc(MAX_LEN_NAME);
    sprintf(argent_texte,"Argent %d $",player.argent);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color black = {0,0,0};
    SDL_Surface * message = TTF_RenderUTF8_Blended(font,argent_texte,black);
    free(argent_texte);
    SDL_Rect argent_rect = {0,0,message->w,message->h};
    SDL_BlitSurface(message,NULL,argent,&argent_rect);
    SDL_Rect arg_rect = {0,0,argent->w,argent->h};
    SDL_BlitSurface(argent,NULL,surface,&argent_rect);
    SDL_Rect container_rect = {x_map,y_map,surface->h,surface->w};
    SDL_BlitSurface(surface,NULL,screen,&container_rect);
    SDL_UpdateWindowSurface(window);
}
/*Afficher le centre pokemon*/
void printMarket(SDL_Window *window,SDL_Surface * screen,player_t player,int colission[1600]){
    SDL_Surface * map = IMG_Load("../tiledmap/market_map.png");
    Uint32 bg = 0x000000;
    SDL_FillRect(screen,NULL,bg);
    SDL_Rect rect = {(WIDTH - map->w)/2,(HEIGHT - map->h)/2,map->w,map->h};
    int x_map = (WIDTH - map->w)/2;
    int y_map = (HEIGHT - map->h)/2;
    
    SDL_BlitSurface(map,NULL,screen,&rect);
    SDL_FreeSurface(map);
    SDL_Log("x == %d\ty == %d",x_map,y_map);
    printSpiritInMarket(window,screen,"images/mec.png",100,100,player,x_map,y_map,colission);
    SDL_UpdateWindowSurface(window);
}
/*verification des coordonnées*/
int coordonnesValide(int colission[1600],int x,int y){
    SDL_Log("%d",colission[(y/16)*40+(x/16)]);
    if(colission[(y/16)*40+(x/16)]&&colission[(y/16)*40+(x/16)]!=porte_market&&colission[(y/16)*40+(x/16)]!=store&&colission[(y/16)*40+(x/16)]!=dame)
        return 0;
    return 1;
}
/*detecter les points d'achats et le sortie*/
int detecteur(SDL_Window *window,SDL_Surface *screen,int col[1600],int x,int y){
    SDL_Log("here in %d",col[col[(y/16)*40+(x/16)]]);
    SDL_Rect rect = {0,800,WIDTH,HEIGHT-700};
    Uint32 bg = 0x000000;
    int retour;
    SDL_FillRect(screen,&rect,bg);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color white = {255,255,255};
    SDL_Surface * message = TTF_RenderUTF8_Blended(font,"",white);
    if(col[(y/16)*40+(x/16)]==porte_market){
        message = TTF_RenderUTF8_Blended(font,"Cliquez sur Q pour sortir",white);
        retour = PORTE;
    }else if(col[(y/16)*40+(x/16)]==dame){
        message = TTF_RenderUTF8_Blended(font,"Cliquez sur H pour soigner votre SDLon",white);
        retour = DAME;
    }else if(col[(y/16)*40+(x/16)]==store){
        message = TTF_RenderUTF8_Blended(font,"Cliquez sur A pour Acheter",white);
        retour = STORE;
    }else{
        return VIDE;
    }
    SDL_Rect container = {(WIDTH - message->w)/2,810,message->w,message->h};
    SDL_BlitSurface(message,NULL,screen,&container);
    SDL_UpdateWindowSurface(window);
    SDL_FreeSurface(message);
    TTF_CloseFont(font);
    return retour;
}
/*afficher le personnage sur la map*/
void printSpiritInMarket(SDL_Window *window,SDL_Surface * screen,char *nom_fichier,int x,int y,player_t player,int x_map,int y_map,int colission[1600]){
    SDL_Surface * spirit = IMG_Load(nom_fichier);
    int movePers=1,i=0,detecter=VIDE;
    item_init();
    SDL_Log("x == %d\ty == %d",x_map,y_map);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color white = {255,255,255};
    SDL_Rect rect = {x_map+x,y+y_map,32,32};
    SDL_Rect copy_rect = {0,0,32,32};
    sdlon_init();
    enum directions dir = DOWN;
    enum actions act = DEF1;
// prq 32 et pas 16 pcq on veut recuperer les 4 part du personnage
    SDL_Rect src_rect = {dir*16,act*16,32,32};
    SDL_Surface* copy = SDL_CreateRGBSurface(0, 32, 32, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_BlitSurface(screen,&rect,copy,&copy_rect);
    SDL_BlitSurface(spirit,&src_rect,screen,&rect);
    //SDL_FreeSurface(spirit);
    SDL_UpdateWindowSurface(window);
    int running = 1;
    int move = 0;
    Uint32 start_time = SDL_GetTicks(); // 100 milliseconds per frame
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
                    case SDLK_s:
                        sspi(player);
                     break;

                    case SDLK_i:
                        int retour = afficherTableauMenu(window,screen,500,700);
                        switch (retour){
                            // sdlon sac informations
                        case 1:
                            sspi(player);
                            break;
                        case 2:;
                            int nbRetour = showAllSDlons(window,screen,4,player);
                            handle_sdlons_inventaire_events(window,screen,nbRetour,player);
                            break;
                        case 3:;
                            //char * noms[5] = {"Sdlasso","Super-sdlasso","CABB-sdlasso","Relique","Extracteur"};
                            //char * descs[5] = {"Un objet particulier qui permet de capturer des sdlons.","Un sdlasso renforcer et amélioré qui permet de capturer des sdlons avec un meilleuhr rendement.","Un objet basé sur le fonctionnement des des sdlasso mais perfectionné par des artisants pour fonctionner à tous les coups.","Une relique êxtremement rare n'ayant que peu d'intêret.","Un outil pouvant être utilisé par des chercheur permettant l'extraction d'une relique."};
                            
                            char * noms[NB_ITEMS];
                            char * descs[NB_ITEMS];
                            display_all_items();
                            for(i=0;i<NB_ITEMS;i++){
                                noms[i] = malloc(sizeof(char)*MAX_LEN_NAME);
                                descs[i] = malloc(sizeof(char)*MAX_LEN_DESCR);
                                strcpy(noms[i], items[i].name);
                                strcpy(descs[i], items[i].description);
                            }
                            sdlon sd;
                            int returnValue = showSac(window,screen,noms,descs,5,player,sd);
                            if(returnValue==-1){
                                TTF_CloseFont(font);
                                printMap(window,screen,player);
                            }
                            break;
                        case 4:
                            showCarte(window,screen,player.name,player.nb_current_sdlon,player.argent,player.genre);
                            
                            break;
                        case 5: ;
                            TTF_CloseFont(font);
                            TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
                            char *menus[4] = {"Nouvelle Partie","Charger Partie","Charger Patch","Quitter"};
                            afficherMenu(window,screen,menus,4,font);
                            return ;
                            break;
                        default:
                            break;
                        }
                     break;

                    case SDLK_UP:
                        movePers=1;
                        if(coordonnesValide(colission,x,y-16)){
                            move = 1;
                            dir = UP;
                        }
                        break;
                    case SDLK_DOWN:
                        movePers=1;
                        if(coordonnesValide(colission,x,y+16)){
                            move = 1;
                            dir = DOWN;
                            
                        }
                        break;
                    case SDLK_LEFT:
                        movePers=1;
                        if(coordonnesValide(colission,x-16,y)){
                            move = 1;
                            dir = LEFT;
                            
                        }
                        break;
                    case SDLK_RIGHT:
                        move=1;
                        if(coordonnesValide(colission,x+16,y)){
                            movePers = 1;
                            dir = RIGHT;
                            
                        }
                        break;
                    /*case SDLK_f:
                        if(dansLesBuissons==PORTE){
                            printMarket(window,screen,player,hintSliceFromMap,hint,collision);
                            return ;
                        }
                        break;*/
                    case SDLK_h:
                        move=0;
                        movePers=0;
                        if(detecter==DAME){
                            player.sd[player.sd_in_use].vie = player.sd[player.sd_in_use].vie_max;
                        }
                        break;
                    case SDLK_q:
                        move=0;
                        movePers=0;
                        if(detecter==PORTE){
                            printMap(window,screen,player);
                        }
                        break;
                    case SDLK_a:
                    SDL_Log("go to store1");
                        move=0;
                        movePers=0;
                        if(detecter==STORE){
                            SDL_FillRect(screen,NULL,0x000000);
                            SDL_Log("go to store2");
                            SDL_Surface * surface = SDL_CreateRGBSurface(0, 640, 640, screen->format->BitsPerPixel, 0, 255, 255, 255);
                            afficherLaBoutique(window,screen,surface,player,x_map,y_map);
                        }
                        break;
                    
                    default:
                        move=0;
                        break;
                }
                //dansLesBuissons = detecterBuissons(window,screen,x+16,y+16,hintSliceFromMap,hint,font,white,movePers);
                
                break;
            case SDL_MOUSEMOTION:
                break;
            }
               
        }
        if(move){
            if(dir==UP){
                detecter = detecteur(window,screen,colission,x,y);
                SDL_Rect nouv_rect = {rect.x,rect.y-16,rect.h,rect.w};
                            movePlayer(window,spirit,screen,copy,rect,nouv_rect,UP,WALK1,&start_time);
                            rect.y = nouv_rect.y;
                            y=y-16;
                    }
                    if(dir==DOWN){
                        SDL_Rect nouv_rect = {rect.x,rect.y+16,rect.h,rect.w};
                            movePlayer(window,spirit,screen,copy,rect,nouv_rect,DOWN,WALK1,&start_time);
                            rect.y = nouv_rect.y;
                            y=y+16;
                    }
                    if(dir==LEFT){
                        SDL_Rect nouv_rect = {rect.x-16,rect.y,rect.h,rect.w};
                            movePlayer(window,spirit,screen,copy,rect,nouv_rect,LEFT,WALK1,&start_time);
                            rect.x = nouv_rect.x;
                            x=x-16;
                    }
                    if(dir==RIGHT){
                        SDL_Rect nouv_rect = {rect.x+16,rect.y,rect.h,rect.w};
                            movePlayer(window,spirit,screen,copy,rect,nouv_rect,RIGHT,WALK1,&start_time);
                            rect.x = nouv_rect.x;
                            x=x+16;
                    }
                    
        } 
        if (SDL_GetTicks() - start_time > 2000){
                    Uint32 start_temps = SDL_GetTicks();
                    movePlayer(window,spirit,screen,copy,rect,rect,dir,DEF1,&start_temps);
                    movePlayer(window,spirit,screen,copy,rect,rect,dir,DEF2,&start_temps);
        }
    }
}