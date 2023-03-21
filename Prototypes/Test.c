#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>



int main(){
    SDL_Window *window;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("Erreur d'initialisation de SDL : %s\n", SDL_GetError());
      return 1;
    }
    
    window = SDL_CreateWindow("Ma fenêtre SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 2000, 2000, SDL_WINDOW_SHOWN);
    if (!window) {
      printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
      SDL_Quit();
      return 1;
    }

    SDL_Surface *image = IMG_Load("./sdlon/img/map_villeA.png");
    if (!image) {
      printf("Erreur de chargement de l'image : %s\n", IMG_GetError());
      SDL_Quit();
      return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
      printf("Erreur de création du rendeur : %s\n", SDL_GetError());
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
    }


    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      printf("Erreur de conversion en texture : %s\n", SDL_GetError());
      SDL_FreeSurface(image);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
    }
    SDL_Rect sourceRect = {0, 0,image->w,image->h};
    SDL_Rect destRect = {0, 0,image->w,image->h};
    
    SDL_FreeSurface(image);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_RenderPresent(renderer);


    
    int quit = 0;
    SDL_Event event;
    while (!quit) {
      while (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            quit = 1;
         }
      }
        destRect.x++;
        //destRect.y++;

      // Effacer l'écran
      SDL_RenderClear(renderer);

      // Copier la texture sur le rendeur
      SDL_RenderCopy(renderer, texture,   NULL, &destRect);

      // Mettre à jour l'affichage
      SDL_RenderPresent(renderer);
   } 
    
    
    
    
    
    
    
    SDL_Delay(3000);


    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}