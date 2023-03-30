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
void afficherItem(SDL_Window *window,SDL_Surface * surface,char * nom, int prix,int y, player_t player, int index){
    /*Varibles*/
    Uint32 bg = 0xFFFFFF;
    SDL_Color color = {96,96,96};
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    
    /*Conatiner*/
    SDL_Surface *item_container = SDL_CreateRGBSurface(0, 640-337, 50, 32, 0, 255, 255, 255);
    SDL_FillRect(item_container,NULL,bg);
    /*texte d'item*/
    SDL_Surface *item_name = TTF_RenderUTF8_Blended(font,nom,color);
    SDL_Rect rect_texte = {30,10,item_name->h,item_name->w};
    SDL_BlitSurface(item_name,NULL,item_container,&rect_texte);
    SDL_FreeSurface(item_name);
    /*quantite d'item*/
    char * nombre = malloc(sizeof(char )* MAX_LEN_NAME);
    
    sprintf(nombre,"$ %d", prix);
    SDL_Surface *item_quant = TTF_RenderUTF8_Blended(font,nombre,color);
    free(nombre);
    SDL_Rect rect_qnt = {(item_container->w - item_quant->w - 20),10,item_quant->h,item_quant->w};
    SDL_BlitSurface(item_quant,NULL,item_container,&rect_qnt);
    SDL_FreeSurface(item_quant);
    SDL_Log("here 3\n");
    /**/
    SDL_Rect rect_container = {337,y,item_container->h,item_container->w};
    SDL_BlitSurface(item_container,NULL,surface,&rect_container);
    SDL_FreeSurface(item_container);
    TTF_CloseFont(font);
}

int confirmation(SDL_Window * window,SDL_Surface * screen,SDL_Surface * surface,int x,int y,SDL_Rect container_rect,int i){
    SDL_Log("x == %d,y == %d",x,y);
    SDL_Surface *container = SDL_CreateRGBSurface(0, 300, 80, 32, 0, 255, 255, 255);
    SDL_FillRect(container,NULL,0xffffff);
    SDL_Surface *up = IMG_Load("images/up.png");
    SDL_Rect rect_up = {10,0,up->w,up->h};
    SDL_Surface *down = IMG_Load("images/down.png");
    SDL_Rect rect_down = {10,55,down->w,down->h};
    char * quantite = malloc(MAX_LEN_NAME);
    int totlaObjets = 0;
    sprintf(quantite,"x%d",totlaObjets);
    SDL_Color black = {0,0,0};
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Surface * qnt = TTF_RenderUTF8_Blended(font,quantite,black);
    SDL_Rect quantite_rect = {10,25,qnt->w,qnt->h};
    SDL_BlitSurface(up,NULL,container,&rect_up);
    SDL_BlitSurface(qnt,NULL,container,&quantite_rect);
    SDL_BlitSurface(down,NULL,container,&rect_down);
    char * somme = malloc(MAX_LEN_NAME);
    int total = 0;
    
    sprintf(somme,"$    %d",total);
    SDL_Surface * som = TTF_RenderUTF8_Blended(font,somme,black);
    SDL_Rect somme_rect = {container->w - 60 - som->w ,25,som->w,som->h};
    SDL_BlitSurface(som,NULL,container,&somme_rect);
    SDL_Rect rect = {400,500,container->w,container->h};
    SDL_BlitSurface(container,NULL,surface,&rect);
    SDL_BlitSurface(surface,NULL,screen,&container_rect);
    SDL_UpdateWindowSurface(window);
    int running = 1;
    SDL_Point mousePosition;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        totlaObjets++;
                        total += items[i].prix;// a changer
                        break;
                    case SDLK_DOWN:
                        if(totlaObjets>0){
                            totlaObjets--;
                            total -= items[i].prix;// a changer
                        }
                        break;
                    case SDLK_RETURN:
                        SDL_FillRect(container,NULL,0xffffff);
                        SDL_BlitSurface(container,NULL,surface,&rect);
                        SDL_BlitSurface(surface,NULL,screen,&container_rect);
                        SDL_UpdateWindowSurface(window);
                        return total*-1;
                        break;
                }
                SDL_FillRect(container,NULL,0xffffff);
                SDL_BlitSurface(container,NULL,surface,&rect);
                SDL_BlitSurface(surface,NULL,screen,&container_rect);
                SDL_UpdateWindowSurface(window);
                SDL_BlitSurface(up,NULL,container,&rect_up);
                SDL_BlitSurface(down,NULL,container,&rect_down);
                //qnt
                sprintf(quantite,"x%d",totlaObjets);
                qnt = TTF_RenderUTF8_Blended(font,quantite,black);
                SDL_Rect quantite_rect = {10,25,qnt->w,qnt->h};
                SDL_BlitSurface(qnt,NULL,container,&quantite_rect);
                //total
                sprintf(somme,"$    %d",total);
                som = TTF_RenderUTF8_Blended(font,somme,black);
                SDL_Rect somme_rect = {container->w - 60 - som->w ,25,som->w,som->h};
                SDL_BlitSurface(som,NULL,container,&somme_rect);
                //update window
                SDL_BlitSurface(container,NULL,surface,&rect);
                SDL_BlitSurface(surface,NULL,screen,&container_rect);
                SDL_UpdateWindowSurface(window);
          }
        }
    }
}

void afficherDescription(SDL_Window *window,SDL_Surface * screen,SDL_Surface * surface,SDL_Surface *sac,SDL_Surface *argent,char * desc,SDL_Rect container_rect){
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Surface *desc_container = SDL_CreateRGBSurface(0, 640/2, 640-(sac->h+argent->h), 32, 0, 255, 255, 255);
    SDL_FillRect(desc_container,NULL,0xFFFFFF);
    SDL_Color white = {0,0,0};
    SDL_Surface *desc_texte = TTF_RenderText_Blended_Wrapped(font,desc,white,desc_container->w);
    SDL_Rect rect_texte = {10,10,desc_texte->h,desc_texte->w};
    SDL_BlitSurface(desc_texte,NULL,desc_container,&rect_texte);
    SDL_FreeSurface(desc_texte);
    SDL_Rect rect_container = {0,sac->h+argent->h+100,desc_texte->h,desc_texte->w};
    SDL_BlitSurface(desc_container,NULL,surface,&rect_container);
    SDL_FreeSurface(desc_container);
    SDL_BlitSurface(surface,NULL,screen,&container_rect);
    SDL_UpdateWindowSurface(window);
}

/**
 * fonction d'affichage de la boutique 
*/
void afficherLaBoutique(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,player_t *player,int x_map,int y_map){
    SDL_FillRect(surface,NULL,0xffffff);
    char * argent_texte = malloc(MAX_LEN_NAME);
    sprintf(argent_texte,"Argent                                     %d $",player->argent);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color black = {0,0,0};
    SDL_Surface * message = TTF_RenderUTF8_Blended(font,argent_texte,black);
    SDL_Surface * argent = SDL_CreateRGBSurface(0, message->w + 10,20+message->h, surface->format->BitsPerPixel, 0, 255, 255, 255);
    SDL_FillRect(argent,NULL,0xffffff);
    free(argent_texte);
    SDL_Rect argent_rect = {5,10,message->w,message->h};
    SDL_BlitSurface(message,NULL,argent,&argent_rect);
    SDL_Rect arg_rect = {0,0,argent->w,argent->h};
    SDL_BlitSurface(argent,NULL,surface,&arg_rect);
    SDL_Rect container_rect = {x_map,y_map,surface->h,surface->w};
    //image
    SDL_Surface * sac = IMG_Load("images/sac.png");
    SDL_Surface * image_container = SDL_CreateRGBSurface(0, sac->w,sac->h, surface->format->BitsPerPixel, 0, 255, 255, 255);
    SDL_FillRect(image_container,NULL,0xa51209);
    SDL_Rect image_rect = {0,0,sac->w,sac->h};
    SDL_BlitSurface(sac,NULL,image_container,&image_rect);
    SDL_Rect image_cont_rect = {0,argent->h,image_container->w,image_container->h};
    SDL_BlitSurface(image_container,NULL,surface,&image_cont_rect);
    //description
    SDL_Surface *desc_container = SDL_CreateRGBSurface(0, 640/2, 640-(sac->h+argent->h), 32, 0, 255, 255, 255);
    SDL_FillRect(desc_container,NULL,0xFFFFFF);
    SDL_Color white = {0,0,0};
    SDL_Surface *desc_texte = TTF_RenderText_Blended_Wrapped(font,items[0].description,white,desc_container->w);
    SDL_Rect rect_texte = {10,10,desc_texte->h,desc_texte->w};
    SDL_BlitSurface(desc_texte,NULL,desc_container,&rect_texte);
    SDL_FreeSurface(desc_texte);
    SDL_Rect rect_container = {0,sac->h+argent->h+100,desc_texte->h,desc_texte->w};
    SDL_BlitSurface(desc_container,NULL,surface,&rect_container);
    SDL_FreeSurface(desc_container);
    //item
    for(int i=0;i<NB_ITEMS;i++)
        afficherItem(window,surface,items[i].name,items[i].prix,50*i,*player,0);
    

    int n = 5;
    SDL_Rect btn = {337,600,320,40};
    SDL_Rect btn_in_screen = {337+x_map,600+y_map,320,40};
    botton(surface,"Quitter",btn.w, btn.h, btn.x, btn.y, 0);
    
    //arrow
    int nb=0;
    SDL_Surface * arrow =  IMG_Load("images/select.png");
    SDL_Rect rect_arrow = {5+337,(50)*(nb)+15,arrow->h,arrow->w};
    SDL_BlitSurface(arrow,NULL,surface,&rect_arrow);
    int etape = 0;
    SDL_BlitSurface(surface,NULL,screen,&container_rect);
    SDL_UpdateWindowSurface(window);
    int running = 1;
    SDL_Point mousePosition;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_MOUSEBUTTONUP:
                if(SDL_PointInRect(&mousePosition, &btn_in_screen)){
                    if(sac)
                        SDL_FreeSurface(sac);
                    SDL_FreeSurface(surface);
                    SDL_FreeSurface(arrow);
                    SDL_Log("should quit");
                    return;
                }
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        nb=(nb-1);
                        nb = (nb<0)?(nb + n):(nb);
                        break;
                    case SDLK_DOWN:
                        nb=(nb+1)%n;
                        break;
                    case SDLK_RETURN:
                        SDL_Log("player argent avant %d",player->argent);
                        int total = confirmation(window,screen,surface,x_map+340,500,container_rect,nb);
                        int qtt = (total/items[nb].prix)*(-1);
                        player->argent += total;
                        add_items(nb,qtt,player);
                        SDL_Log("player argent apres %d",player->argent);
                        SDL_FillRect(screen,NULL,0x000000);
                        afficherLaBoutique(window,screen,surface,player,x_map,y_map);
                        return;
                        break;
                }
                SDL_FillRect(surface,&rect_arrow,0xffffff);
                afficherDescription(window,screen,surface,sac,argent,items[nb].description,container_rect);
                /*SDL_Log("%s",items[nb].path);
                sac = IMG_Load(items[nb].path);
                SDL_Rect rect = {100,100,sac->h,sac->w};
                //SDL_Rect rect2 = {0,0,sac->h,sac->w};
                SDL_FillRect(screen,&rect,bg);
                SDL_BlitSurface(sac,NULL,screen,&rect);
                SDL_UpdateWindowSurface(window);*/
                break;
            case SDL_MOUSEMOTION:
                mousePosition.x = e.motion.x; 
                mousePosition.y = e.motion.y;
                if (SDL_PointInRect(&mousePosition, &btn_in_screen)){
                    botton(surface,"Quitter",btn.w, btn.h, btn.x, btn.y, 1);
                }else
                    botton(surface,"Quitter",btn.w, btn.h, btn.x, btn.y, 0);
                SDL_BlitSurface(surface,NULL,screen,&container_rect);
                
                SDL_UpdateWindowSurface(window);
          }
                rect_arrow.y = (50)*(nb)+15;
                SDL_BlitSurface(arrow,NULL,surface,&rect_arrow);
                
                SDL_BlitSurface(surface,NULL,screen,&container_rect);
                SDL_UpdateWindowSurface(window);
        }
    }
}

/**
 * Afficher le centre sdlon
*/
int printMarket(SDL_Window *window,SDL_Surface * screen,player_t *player,char *nom_fichier,int colission[1600]){
    printf("nom du fichier %s\n",nom_fichier);
    SDL_Surface * map = IMG_Load(nom_fichier);
    if(!map)
        printf("error image\n");
    Uint32 bg = 0x000000;
    SDL_FillRect(screen,NULL,bg);
    printf("error here\n");
    SDL_Rect rect = {(WIDTH - map->w)/2,(HEIGHT - map->h)/2,map->w,map->h};
    int x_map = (WIDTH - map->w)/2;
    int y_map = (HEIGHT - map->h)/2;
    
    SDL_BlitSurface(map,NULL,screen,&rect);
    SDL_FreeSurface(map);
    SDL_Log("x == %d\ty == %d",x_map,y_map);
    int var;
    if(player->genre==HOMME)
        var = printSpiritInMarket(window,screen,"images/mec.png",305,550,*player,x_map,y_map,colission);
    else
        var = printSpiritInMarket(window,screen,"images/meuf.png",305,550,*player,x_map,y_map,colission);
    SDL_UpdateWindowSurface(window);
    return var;
}
/**
 * fonction verification des coordonnées
*/
int coordonnesValide(int colission[1600],int x,int y){
    SDL_Log("%d",colission[(y/16)*40+(x/16)]);
    if(colission[(y/16)*40+(x/16)]&&colission[(y/16)*40+(x/16)]!=porte_market&&colission[(y/16)*40+(x/16)]!=store&&colission[(y/16)*40+(x/16)]!=dame)
        return 0;
    return 1;
}

/**
 * Detectcte les points de:
 * - Achat
 * - Sortie
 * - Soins
*/
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

/**
 * Gestion de ses collisions
 * Affichage du personnages dans la map
 * 
*/
int printSpiritInMarket(SDL_Window *window,SDL_Surface * screen,char *nom_fichier,int x,int y,player_t player,int x_map,int y_map,int colission[1600]){
    SDL_Surface * spirit = IMG_Load(nom_fichier);
    int movePers=1,i=0,detecter=VIDE,retour;
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
                        retour = afficherTableauMenu(window,screen,500,700);
                        switch (retour){
                            // sdlon sac informations
                        case 1:
                            sspi(player);
                            break;
                        case 2:;
                            int nbRetour = showAllSDlons(window,screen,4,player);
                            printMarket(window,screen,&player,"../tiledmap/market_map.png",market_collision);
                            //if(nbRetour==player.nb_current_sdlon)
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
                            int returnValue = showSac(window,screen,noms,descs,5,&player,sd);
                            if(returnValue==-1){
                                TTF_CloseFont(font);
                                printMarket(window,screen,&player,"../tiledmap/market_map.png",market_collision);
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
                            int nb_sd=0;
                            for(nb_sd=0;nb_sd<player.nb_current_sdlon;nb_sd++){
                                player.sd[nb_sd].vie = player.sd[nb_sd].vie_max;
                            }
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
                            
                            SDL_Log("go to store2");
                            SDL_Surface * surface = SDL_CreateRGBSurface(0, 640, 640, screen->format->BitsPerPixel, 0, 255, 255, 255);
                            afficherLaBoutique(window,screen,surface,&player,x_map,y_map);
                            SDL_FillRect(screen,NULL,0x000000);
                            printMarket(window,screen,&player,"../tiledmap/market_map.png",market_collision);
                            return -1;
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