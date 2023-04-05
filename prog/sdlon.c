# include <stdio.h>
# include <string.h>
# include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <dirent.h>
# include "map.h"
#include "include/player.h"
#include "combat.h"
#include "intro/sdl_intro_test.h"
#define HEIGHT 840
#define WIDTH  1280

/*
sommet y = 480 -> -1590

*/

/*
cd C:\Users\bdalh\Desktop\test
gcc sdl_test.c -IC:\Users\bdalh\Desktop\developpement\x86_64-w64-mingw32\include -LC:\Users\bdalh\Desktop\developpement\x86_64-w64-mingw32\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -o prog
*/
/*detruire l'ecran*/
void destroy_all(SDL_Window *pWindow,TTF_Font *font);
/*fonction pour afficher le menu d'accueil*/
void afficherMenu(SDL_Window *pWindow, SDL_Surface *screen,char *menus[],int N,TTF_Font *font);
/*fonction pour afficher les sauvegardes disponibles*/
void afficherLesSauvegardes(SDL_Window *pWindow,SDL_Surface * screen,TTF_Font *font,char strings[][100],int N,SDL_Rect *rect){
  sdlon_init();
  SDL_Rect rects[N];
  SDL_Color white = {255,255,255};
  int y = (HEIGHT - (50*2) - (50*N))/N;
  for(int i=0;i<N;i++){
    rects[i].y = y;
    SDL_Surface *texte = TTF_RenderUTF8_Blended(font,strings[i],white);
    rects[i].x = (WIDTH - 200 )/2;
    rects[i].h = 50;
    rects[i].w = 200;
    SDL_FillRect(screen,&rects[i],SDL_MapRGB(screen->format,180,180,180));
    rects[i].x = (WIDTH - texte->w )/2;
    rects[i].y += (texte->h)/2;
    SDL_BlitSurface(texte,NULL,screen,&rects[i]);
    SDL_FreeSurface(texte);
    y+=55;
  }
  SDL_UpdateWindowSurface(pWindow);
    SDL_Event e;
  SDL_Point mousePosition;
  while(1){
    while(SDL_PollEvent(&e)) { 
      switch(e.type){
        case SDL_QUIT:
        destroy_all(pWindow,font);
        break;
        case SDL_MOUSEBUTTONUP:
          mousePosition.x = e.motion.x; 
          mousePosition.y = e.motion.y;
            if (SDL_PointInRect(&mousePosition, rect)) {
              SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
              SDL_UpdateWindowSurface(pWindow);
              char *menus[4] = {"Nouvelle Partie","Charger Partie","Charger Patch","Quitter"};
              return afficherMenu(pWindow,screen,menus,4,font);
            } 
            for (int i = 0; i < N; i++){
              if (SDL_PointInRect(&mousePosition, &rects[i])) {
                player_t player = player_init(strings[i]);
                TTF_CloseFont(font);
                if(player.current_town==0)
                  printMap(pWindow,screen,player,collision,buissons);
                else if(player.current_town==1)
                  printMap(pWindow,screen,player,collision_map_2,buissons_map2);
              } 
            }
            
            break;
      }
      }
    }
  
}
/*detruire l'ecran*/
void destroy_all(SDL_Window *pWindow,TTF_Font *font){
  SDL_DestroyWindow(pWindow);
    TTF_CloseFont(font); /* Doit etre avant T T F _ Q u i t () */
    TTF_Quit();
    SDL_Quit();
    exit(1);
}
/*fonction qui affiche l'interface de nouvelle partie*/
void newSaveGame(SDL_Window *pWindow,TTF_Font *font,SDL_Surface *screen){
  sdlon_init();
  SDL_Color white = {255,255,255};
  SDL_Color red = {255,0,0};
  SDL_Surface *name;
  SDL_Surface *btn = TTF_RenderUTF8_Blended(font,"Commencer",white),*retour=TTF_RenderUTF8_Blended(font,"retour",white),*error=TTF_RenderUTF8_Blended(font,"",red);
  SDL_Surface *welcomeMsg = TTF_RenderUTF8_Blended(font,"Bienvenue dans SDLon",white);
  SDL_Surface *instrctionMsg = TTF_RenderUTF8_Blended(font,"Veuillez saisir votre nom",white);
  SDL_Rect rect,btnRect,retourRect;
  rect.x = (WIDTH - welcomeMsg->w)/2;
  rect.y = 50;
  rect.h = welcomeMsg->h;
  rect.w = welcomeMsg->w;
  
  SDL_BlitSurface(welcomeMsg,NULL,screen,&rect);
  rect.y=800;
  btnRect.x=rect.x + btn->w;
  btnRect.y=rect.y;
  btnRect.h=rect.h;
  btnRect.w=rect.w;
  SDL_BlitSurface(btn,NULL,screen,&btnRect);
  retourRect.x=rect.x - retour->w;
  retourRect.y=rect.y;
  retourRect.h=rect.h;
  retourRect.w=rect.w;
  SDL_BlitSurface(retour,NULL,screen,&retourRect);
      SDL_FreeSurface(welcomeMsg);
      SDL_FreeSurface(btn);
      SDL_FreeSurface(retour);
      rect.y = 100;
      rect.x = (WIDTH - instrctionMsg->w)/2;
     SDL_BlitSurface(instrctionMsg,NULL,screen,&rect);
      SDL_FreeSurface(instrctionMsg);
      SDL_UpdateWindowSurface(pWindow);
      rect.y=300;
  char savaGameName[255]={""};
  int index = 0;
  int running =1;
  SDL_StartTextInput();
  SDL_Event e;
  SDL_Point mousePosition;
  while(running){
    while(SDL_PollEvent(&e)) { 
        
        if(e.type ==SDL_KEYDOWN&&e.key.keysym.sym==SDLK_BACKSPACE&&index>0){
          index--;
          name = TTF_RenderUTF8_Blended(font,savaGameName, white);
          SDL_BlitSurface(name,NULL,screen,&rect);
          SDL_FreeSurface(name);
          if(index==0)
            savaGameName[index]=' ';
          else
            savaGameName[index]='\0';
          name = TTF_RenderUTF8_Blended(font,savaGameName, white);
          rect.x = (WIDTH - name->w)/2;
          SDL_BlitSurface(name,NULL,screen,&rect);
          SDL_FreeSurface(name);
          SDL_UpdateWindowSurface(pWindow);
          
        }
        else if(e.type== SDL_TEXTINPUT&&index<10){
          strcat(savaGameName,e.text.text);
          index++;
          savaGameName[index]='\0';
          
          name = TTF_RenderUTF8_Blended(font,savaGameName,white);
          
          SDL_BlitSurface(name,NULL,screen,&rect);
          SDL_FreeSurface(name);
          SDL_UpdateWindowSurface(pWindow);
        }
        if(e.type==SDL_MOUSEBUTTONUP){
            mousePosition.x = e.motion.x; 
            mousePosition.y = e.motion.y;
              if (SDL_PointInRect(&mousePosition, &btnRect)) {
                if(index==0){
                  error = TTF_RenderUTF8_Blended(font,"Veuillez saisir votre nom de Sauvegarde",red);
                  rect.x = (WIDTH - error->w)/2;
                  rect.y=500;
                  SDL_BlitSurface(error,NULL,screen,&rect);
                  SDL_FreeSurface(error);
                  SDL_UpdateWindowSurface(pWindow);
                }else{
                  SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
                  // frees
                SDL_FreeSurface(error);
                  int genre = afficherCinematique(pWindow,screen);
                  printf("fin de cinématique");
                  char * name = malloc(sizeof(char)*MAX_LEN_NAME);
                  strcpy(name, savaGameName);
                  player_t player = player_create(name, genre, name);
                  player.x = 50*16;
                  player.y = 23*16;
                  sspi(player);
                  // frees
                  SDL_FreeSurface(error);
                  TTF_CloseFont(font);
                  if(player.current_town==0)
                    printMap(pWindow,screen,player,collision,buissons);
                  else if(player.current_town==1)
                    printMap(pWindow,screen,player,collision_map_2,buissons_map2);

                  destroy_all(pWindow,font);
                }
                
              }else if (SDL_PointInRect(&mousePosition, &retourRect)) {
                SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
                char *menus[4] = {"Nouvelle Partie","Charger Partie","Charger Patch","Quitter"};
                // frees
                SDL_FreeSurface(error);
                return afficherMenu(pWindow,screen,menus,4,font);
              }
        }
        if(e.type==SDL_QUIT){
          running=0;
          }
      }
    }
    SDL_StopTextInput();
  destroy_all(pWindow,font);
  }
/*fonction qui affiche chaque sauvegarde separement*/ 
void getSaveGames(SDL_Window *pWindow,TTF_Font *font,SDL_Surface *screen){
  SDL_Rect rect;
  SDL_Color white = {255,255,255};
  SDL_Surface *title = TTF_RenderUTF8_Blended(font,"Charger une partie...",white);
  rect.x = (WIDTH - title->w)/2;
  rect.y = 30;
  rect.h = title->h;
  rect.w = title->w;
  SDL_BlitSurface(title,NULL,screen,&rect);
  title = TTF_RenderUTF8_Blended(font,"Retour",white);
  rect.y = HEIGHT - 100;
  SDL_BlitSurface(title,NULL,screen,&rect);
  SDL_FreeSurface(title);
  SDL_UpdateWindowSurface(pWindow);
  DIR *d;
  char fileNames[20][100];
  int index=0;
  struct dirent *dir;
  d = opendir("include/data/players_data");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if(strcmp(dir->d_name,".")!=0&&strcmp(dir->d_name,"..")!=0){
        strcpy(fileNames[index],dir->d_name);
        index++;
      }
        
    }
    closedir(d);
  }
  afficherLesSauvegardes(pWindow,screen,font,fileNames,index,&rect);
  SDL_Event e;
  SDL_Point mousePosition;
  while(1){
    while(SDL_PollEvent(&e)) { 
      switch(e.type){
        case SDL_QUIT:
          destroy_all(pWindow,font);
        break;
        case SDL_MOUSEBUTTONUP:
          mousePosition.x = e.motion.x; 
          mousePosition.y = e.motion.y;
            if (SDL_PointInRect(&mousePosition, &rect)) {
              SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
              SDL_UpdateWindowSurface(pWindow);
              char *menus[4] = {"Nouvelle Partie","Charger Partie","Charger Patch","Quitter"};
              afficherMenu(pWindow,screen,menus,4,font);
            } 
          break;
      }
      }
    }
  return destroy_all(pWindow,font);
}
/*fonction pour afficher le menu d'accueil*/
void afficherMenu(SDL_Window *pWindow, SDL_Surface *screen,char *menus[],int N,TTF_Font *font){
    
    SDL_Surface *img_bg = IMG_Load("images/asset/scene_de_combat/sdlon.jpg");

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_BlitSurface(img_bg, NULL, screen, NULL);
    SDL_Surface *btns[N];
    SDL_Color colors[2] = {{255,255,255},{0,0,0}};
    SDL_Rect rects[N];
    int active[N];
    int i;

    while(1){
      for( i=0;i<N;i++){
      btns[i] = TTF_RenderUTF8_Blended(font,menus[i],colors[1]);
      /**/
      rects[i].w =200;
      rects[i].h = btns[i]->h;
      rects[i].x = (WIDTH - 100 - (btns[i]->w)/2)/2;
      rects[i].y = (HEIGHT - N*btns[i]->h - (N-1)*btns[i]->h)/2 + (i)*2*btns[i]->h;
      printf("%d %d %d %d\n",rects[i].h,rects[i].w,rects[i].x,rects[i].y);
      SDL_BlitSurface(btns[i],NULL,screen,&rects[i]);
      SDL_FreeSurface(btns[i]);
      SDL_UpdateWindowSurface(pWindow);
    }
  SDL_Point mousePosition;
    while(1){
      
      SDL_Event e;
        while (SDL_PollEvent( & e)) {
            switch (e.type) {
            case SDL_MOUSEMOTION:
              mousePosition.x = e.motion.x; 
                mousePosition.y = e.motion.y;
                  for(i=0;i<N;i++){
                    if (SDL_PointInRect(&mousePosition, &rects[i])) {
                      if(!active[i]){
                        active[i]=1;
                        btns[i] = TTF_RenderUTF8_Blended(font,menus[i],colors[0]);
                        SDL_BlitSurface(btns[i],NULL,screen,&rects[i]);
                        SDL_FreeSurface(btns[i]);
                         SDL_UpdateWindowSurface(pWindow);
                        }
                    }else{
                      active[i]=0;
                        btns[i] = TTF_RenderUTF8_Blended(font,menus[i],colors[1]);
                        SDL_BlitSurface(btns[i],NULL,screen,&rects[i]);
                        SDL_FreeSurface(btns[i]);
                         SDL_UpdateWindowSurface(pWindow);
                    }
                  }
              break;
            case SDL_MOUSEBUTTONUP:
                mousePosition.x = e.motion.x; 
                mousePosition.y = e.motion.y;
                  for(i=0;i<N;i++){
                    if (SDL_PointInRect(&mousePosition, &rects[i])) {
                        switch(i){
                          case 0:
                            SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
                            //SDL_BlitSurface(img_bg, NULL, screen, NULL);
                            SDL_UpdateWindowSurface(pWindow);
                            return newSaveGame(pWindow,font,screen);
                            break;
                          case 1:
                            SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
                            //SDL_BlitSurface(img_bg, NULL, screen, NULL);
                            SDL_UpdateWindowSurface(pWindow);
                            return getSaveGames(pWindow,font,screen);
                            break;
                          case 3:
                            return destroy_all(pWindow,font);
                            break;
                        }
                    }
                  }
                
                break;

          case SDL_QUIT:
            destroy_all(pWindow,font) ;
            break;
          }
        }
    }
  

}}

int main(int argc, char ** argv) {
  srand(time(NULL));
  SDL_Log("hello\n");
    // Le p o i n t e u r vers la fenetre
    SDL_Window * pWindow = NULL;
    // Le p o i n t e u r vers la surface incluse dans la fenetre
   
    // Le p o i n t e u r vers notre police
    TTF_Font * police = NULL;
    // Une v a r i a b l e de couleur noire
    
    /* I n i t i a l i s a t i o n simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stdout, " Echec de l ’ initiali sation de la SDL (%s )\n ", SDL_GetError());
      return -1;
    }
    /* I n i t i a l i s a t i o n TTF */
    if (TTF_Init() == -1) {
      fprintf(stderr, " Erreur d ’ i nitialis ation de TTF_Init : %s \n ", TTF_GetError());
      exit(EXIT_FAILURE);
    }
    /* C r e a t i o n de la fenetre */
    pWindow = SDL_CreateWindow(" Sdlon ", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN);
    if (!pWindow) {
      fprintf(stderr, " Erreur a la creation de la fenetre : %s \n ", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    
    if ((police = TTF_OpenFont("OpenSans-Bold.ttf", 25)) == NULL) {
      fprintf(stderr, " erreur  font \n ");
    }
    SDL_Surface * screen;
    screen = SDL_GetWindowSurface(pWindow);
    char *menus[4] = {"Nouvelle Partie","Charger Partie","Charger Patch","Quitter"};

    afficherMenu(pWindow,screen,menus,4,police);
    //afficherLeCombat(pWindow,screen);
    destroy_all(pWindow,police);
    /* Position ou sera mis le texte dans la fenetre */
    // load sample . png into image
    
    return 0;
  }