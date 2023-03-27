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
#include "market.h"
#include <time.h>
#define TILE_SIZE 32
#define WIDTH 1280
#define HEIGHT 832
#define frameTime 100
#define BUISSONS 1
#define PORTE 2

enum directions{DOWN,LEFT,RIGHT,UP};
enum actions{DEF1,WALK1,DEF2,WALK2};

/*------------------------------Variable globales-------------------------------------*/

SDL_Rect hintBox,hintContainer;
SDL_Surface *pasSdlon;
int dansLesBuissons=0;


int printMap(SDL_Window *window,SDL_Surface * screen,player_t player);
//town_init();

void handle_sdlons_inventaire_events(SDL_Window *window,SDL_Surface *screen,int nb,player_t player){
    switch (nb){
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        printMap(window,screen,player);
    // à implémenter après
    default:
        break;
    }
    return;
}

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
    SDL_FreeSurface(tile);
    SDL_UpdateWindowSurface(window);
    
}

int localisationValide(int x,int y){
    if(x<0||x>WIDTH-32||y<0||y>HEIGHT-32)
        return 0;
    if(collision[(y/16)*80+(x/16)]&&collision[(y/16)*80+(x/16)]!=porte)
        return 0;
    return 1;
}

/**
 * Fonctiion qui permet d'afficher la carte d'identité du dresseur
*/
void showCarte(SDL_Window * window,SDL_Surface * screen,char * nom, int nbCurrentSdlons, int argent,int genre){
    int width = 800,height = 400;
    Uint32 bg = 0x2858d8;
    Uint32 bg_photo = 0x1848c8;
    Uint32 bg_main = 0x5e96f8;
    
    /*copy surface*/
    SDL_Surface * copy_carte = SDL_CreateRGBSurface(0, width, height, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_Rect rect_container = {(WIDTH - width)/2,(HEIGHT-height)/2,width,height};
    SDL_Rect rect = {0,0,width,height};
    SDL_BlitSurface(screen,&rect_container,copy_carte,&rect);

    SDL_Surface* carte = SDL_CreateRGBSurface(0, width, height, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_FillRect(carte,NULL,bg);
    // load Photo de dimension 128*128
    SDL_Surface * photo;
    if(genre==HOMME){
        photo = IMG_Load("images/asset/SDLon_character/trainer6.png");
    }else{
        photo = IMG_Load("images/asset/SDLon_character/trainer2.png");
    }
    SDL_Surface* photo_bg = SDL_CreateRGBSurface(0, 128, 128, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_FillRect(photo_bg,NULL,bg_photo);
    SDL_Rect rect_photo = {0,0,128,128};
    SDL_BlitSurface(photo,NULL,photo_bg,&rect_photo);
    SDL_FreeSurface(photo);
    // blit photo in carte
    SDL_Rect photo_rect = {width - 128 - 10,30,128,128};
    SDL_BlitSurface(photo_bg,NULL,carte,&photo_rect);
    SDL_FreeSurface(photo_bg);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color white = {255,255,255};
    // la surface de NOM constante
    
    SDL_Surface *nom_title = TTF_RenderUTF8_Blended(font,"NOM ",white);
    SDL_Surface* nom_container = SDL_CreateRGBSurface(0, width - 128- 40, nom_title->h, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_FillRect(nom_container,NULL,bg_main);
    SDL_Rect nom1 = {10,0,nom_title->h,nom_title->w};
    SDL_BlitSurface(nom_title,NULL,nom_container,&nom1);
    SDL_FreeSurface(nom_title);
    SDL_Surface *nom_player = TTF_RenderUTF8_Blended(font,nom,white);
    SDL_Rect nom2 = {width-128-40 - nom_player->w,0,nom_player->h,nom_player->w};
    SDL_BlitSurface(nom_player,NULL,nom_container,&nom2);
    SDL_FreeSurface(nom_player);
    SDL_Rect rect_nom = {10,60,nom_container->h,nom_container->w};
    SDL_BlitSurface(nom_container,NULL,carte,&rect_nom);
    SDL_FreeSurface(nom_container);
    // la surface de NOMBRE constante
    SDL_Surface *nombre_title = TTF_RenderUTF8_Blended(font,"NOMBRE DE SDLONS ",white);
    SDL_Surface* nombre_container = SDL_CreateRGBSurface(0, width -128 - 40, nombre_title->h, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_FillRect(nombre_container,NULL,bg_main);
    SDL_Rect nombre1 = {10,0,nombre_title->h,nombre_title->w};
    SDL_BlitSurface(nombre_title,NULL,nombre_container,&nombre1);
    SDL_FreeSurface(nombre_title);
    char * nombre = malloc(sizeof(MAX_LEN_NAME));
    sprintf(nombre,"%d",nbCurrentSdlons);
    SDL_Surface *nombre_player = TTF_RenderUTF8_Blended(font,nombre,white);
    SDL_Rect nombre2 = {width-128-40-nombre_player->w,0,nombre_player->h,nombre_player->w};
    SDL_BlitSurface(nombre_player,NULL,nombre_container,&nombre2);
    SDL_FreeSurface(nombre_player);
    SDL_Rect rect_nombre = {10,120,nombre_container->h,nombre_container->w};
    SDL_BlitSurface(nombre_container,NULL,carte,&rect_nombre);
    SDL_FreeSurface(nombre_container);
    // la surface de ARGENT constante
    SDL_Surface *argent_title = TTF_RenderUTF8_Blended(font,"ARGENT ",white);
    SDL_Surface* argent_container = SDL_CreateRGBSurface(0, width -128-40, argent_title->h, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_FillRect(argent_container,NULL,bg_main);
    SDL_Rect argent1 = {10,0,argent_title->h,argent_title->w};
    SDL_BlitSurface(argent_title,NULL,argent_container,&argent1);
    SDL_FreeSurface(argent_title);
    char * arg = malloc(sizeof(MAX_LEN_NAME));
    sprintf(arg,"%d $",argent);
    SDL_Surface *argent_player = TTF_RenderUTF8_Blended(font,arg,white);
    SDL_Rect argent2 = {argent_container->w -argent_player->w,0,argent_player->h,argent_player->w};
    SDL_BlitSurface(argent_player,NULL,argent_container,&argent2);
    SDL_FreeSurface(argent_player);
    SDL_Rect rect_argent = {10,180,argent_container->h,argent_container->w};
    SDL_BlitSurface(argent_container,NULL,carte,&rect_argent);
    SDL_FreeSurface(argent_container);
    //message
    
    SDL_Surface * message = TTF_RenderUTF8_Blended(font,"Je suis DRESSEUR!\nRavi de te connaitre. ",white);
    SDL_Surface* message_bg = SDL_CreateRGBSurface(0, width - 40, message->h, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_FillRect(message_bg,NULL,bg_main);
    SDL_Rect rect_message = {10,0,message->h,message->w};
    SDL_BlitSurface(message,NULL,message_bg,&rect_message);
    SDL_FreeSurface(message);
    SDL_Rect message_rect = {10,240,message_bg->h,message_bg->w};
    SDL_BlitSurface(message_bg,NULL,carte,&message_rect);
    SDL_FreeSurface(message_bg);
    //void botton(SDL_Surface *surface,char * titre,int width,int height,int x,int y,int selected);
    
    botton(carte,"RETOUR",message_bg->w,50,10,300,0);
    
    SDL_Rect btn_in_screen = {10+rect_container.x,300+rect_container.y,message_bg->w,50};
    SDL_BlitSurface(carte,NULL,screen,&rect_container);
    
    SDL_UpdateWindowSurface(window);
    int running = 1;
    SDL_Point mousePosition;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_MOUSEBUTTONUP:
                if(SDL_PointInRect(&mousePosition, &btn_in_screen)){
                    SDL_BlitSurface(copy_carte,NULL,screen,&rect_container);
                    SDL_FreeSurface(copy_carte);
                    SDL_FreeSurface(carte);
                    TTF_CloseFont(font);
                    SDL_UpdateWindowSurface(window);
                    //printMap(window,screen,player);
                    return;
                }
                break;
            case SDL_MOUSEMOTION:
                mousePosition.x = e.motion.x; 
                mousePosition.y = e.motion.y;
                if (SDL_PointInRect(&mousePosition, &btn_in_screen)){
                    botton(carte,"RETOUR",message_bg->w,50,10,300,1);
                }else{
                    botton(carte,"RETOUR",message_bg->w,50,10,300,0);
                }
                SDL_BlitSurface(carte,NULL,screen,&rect_container);
                SDL_UpdateWindowSurface(window);
          }
        }
    }
}

void printSpirit(SDL_Window *window,SDL_Surface * screen,char *nom_fichier,int x,int y,SDL_Surface *hintSliceFromMap,SDL_Surface *hint,player_t player){
    SDL_Surface * spirit = IMG_Load(nom_fichier);
    int movePers=1,i=0,retour;
    item_init();
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color white = {255,255,255};
    printf("image good");
    SDL_Rect rect = {x,y,32,32};
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
                        retour = afficherTableauMenu(window,screen,500,700);
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
                        if(localisationValide(x,y-16)){
                            move = 1;
                            dir = UP;
                        }
                        break;
                    case SDLK_DOWN:
                        movePers=1;
                        if(localisationValide(x,y+16)){
                            move = 1;
                            dir = DOWN;
                            
                        }
                        break;
                    case SDLK_LEFT:
                        movePers=1;
                        if(localisationValide(x-16,y)){
                            move = 1;
                            dir = LEFT;
                            
                        }
                        break;
                    case SDLK_RIGHT:
                        move=1;
                        if(localisationValide(x+16,y)){
                            movePers = 1;
                            dir = RIGHT;
                            
                        }
                        break;
                    case SDLK_f:
                        if(dansLesBuissons==PORTE){
                            printMarket(window,screen,player,market_collision);
                            return ;
                        }
                        break;
                    case SDLK_e:
                        move=0;
                        movePers=0;
                        if(dansLesBuissons==BUISSONS){
                            if(player.nb_current_sdlon<1){
                                // afficher un message indiquant comme quoi il a pas assez de sdlon
                                //SDL_Log("nombre de sdlon insuffisants");
                                sdlon sd = generate_sdlon(0,70,100);
                                add_sdlon_in_set(sd,&player);
                            }else{
                                if(can_fight(player)){
                                    //SDL_Log("E cliqué\n");
                                    //return afficherLeCombat(window,screen);
                                    //sdlon sdl1 = generate_sdlon(0,5,20);
                                    //SDL_Log("nom == %s\n",sdl1.nom);
                                    //decouvrirLeSdlon();
                                    int seed = rand()%100;
                                    //printf("%d\n",seed);
                                    
                                    if(seed<=10){
                                        movePers=0;
                                        sdlon sd = generate_sdlon(0, 1, 15);
                                        TTF_CloseFont(font);
                                        afficherLeCombat(window,screen,player,sd);
                                        
                                    }
                                }else{
                                    printf("Impossible de se battre");
                                }
                                
                            }
                            
                        }
                        break;
                    
                    default:
                        move=0;
                        break;
                }
                dansLesBuissons = detecterBuissons(window,screen,x+16,y+16,hintSliceFromMap,hint,font,white,movePers);
                
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

int printMap(SDL_Window *window,SDL_Surface * screen,player_t player){
    /*town_init();
    int i=0;
    for(i=0;i<all_town[0].nb_layer;i++){
        printLayer(window,screen,all_town[0].layer[i],all_town[0].source_grid,all_town[0].first_grid,all_town[0].tile_width,all_town[0].tile_height);
    }*/
    printLayer(window,screen,sol,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,chemin,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,arbre,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,buissons,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,objets,"images/pokemon_style.png",1,16,16);
    //***
    
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color white = {255,255,255};
    SDL_Surface *hint = TTF_RenderUTF8_Blended(font,"Cliquez sur E pour chercher le sdlon",white);
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
    TTF_CloseFont(font);
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
int detecterBuissons(SDL_Window * window, SDL_Surface * screen,int x,int y,SDL_Surface *hintSliceFromMap,SDL_Surface *hint,TTF_Font *font,SDL_Color white,int move){
    
    SDL_Log("valeurs de collision %d",collision[(y/16)*80+(x/16)]);
    if(move){
        if(collision[(y/16)*80+(x/16)]==porte)
            hint = TTF_RenderUTF8_Blended(font,"Cliquez sur F pour Entrer a la maison",white);
        else
            hint = TTF_RenderUTF8_Blended(font,"Cliquez sur E pour chercher le sdlon",white);
    }
    else{
        hint = TTF_RenderUTF8_Blended(font,"Vous n'avez pas trouve de sdlon",white);
    }
    SDL_BlitSurface(hintSliceFromMap,&hintContainer,screen,&hintBox);
    if(buissons[(y/16)*80+(x/16)]||collision[(y/16)*80+(x/16)]==porte){
        SDL_Log("print message");
        SDL_BlitSurface(hint,&hintContainer,screen,&hintBox);
        SDL_UpdateWindowSurface(window);
        if(collision[(y/16)*80+(x/16)]==porte)
            return PORTE;
        else
            return BUISSONS;
    }else{        
        
        SDL_BlitSurface(hintSliceFromMap,&hintContainer,screen,&hintBox);
        SDL_UpdateWindowSurface(window);
        return 0;
    }
}