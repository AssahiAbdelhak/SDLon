# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include "./lib/lib_sdl_facile.h"

/**
  \file lib_sdl_facile.c
  \brief librairie simplifié pour créer et afficher des éléments
  \author Lilian Colla
  \version 1.0
  \date 16/02/2023
*/


float taille_x(int x){
  return WIDTH/x;
}



float taille_y(int y){
  return HEIGHT/y;
}



void blackscreen(SDL_Renderer * renderer){
  /**
    \brief blackscreen : affiche un ecran noir
  */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(renderer, NULL);
  SDL_RenderPresent(renderer);
}



SDL_Texture * print_image(SDL_Renderer * renderer, char * img, int xi, int yi, int hi, int wi){
  
  
  //-------Message--------
  //fonction pour initialiser une image dans le renderer

  SDL_Surface * image = IMG_Load(img);
  if(!image){
    printf("Erreur de chargement de l'image : %s",SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Rect rectangle;
  rectangle.x=xi;
  rectangle.y=yi;
  rectangle.h=hi;
  rectangle.w=wi;

  
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
  if(!texture){
    printf("Erreur de chargement de la texture : %s",SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_FreeSurface(image);
  SDL_RenderCopy(renderer, texture, NULL, &rectangle);

  return texture ;
}



SDL_Texture * print_text(SDL_Renderer * renderer, const char * fontName, const char * texte, const int xt, const int yt){

  //fonction qui affiche du texte

  TTF_Init();


  TTF_Font * font ;
  if((font = TTF_OpenFont(fontName, 20)) == NULL){
    printf("erreur de chargement de la font\n");
    exit(EXIT_FAILURE);
  }

  //couleur du texte : blanche
  SDL_Color White = {255, 255, 255};

  SDL_Surface * surfMessage;
  surfMessage = TTF_RenderUTF8_Blended(font, texte, White);
  if(!surfMessage){
    printf("erreur de chargement du message\n");
    exit(EXIT_FAILURE);
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Texture * Message = SDL_CreateTextureFromSurface(renderer, surfMessage);
  if(!Message){
    printf("erreur de chargement de la texture\n");
    exit(EXIT_FAILURE);
  }


  SDL_Rect Message_rect;
  Message_rect.x = xt ;//100 -> 100
  Message_rect.y = yt ;//700 -> 750

  SDL_QueryTexture(Message, NULL, NULL, &(Message_rect.w), &(Message_rect.h));

  SDL_FreeSurface(surfMessage);
  SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
  TTF_Quit();

  return Message ;
}



void affichage(SDL_Renderer * renderer){
  //Pour la finalisation et l'affichage
  SDL_RenderPresent(renderer);
}

void PrintKeyInfo(SDL_KeyboardEvent * key){
  if(key->type == SDL_KEYUP)
    printf("Release:- ");
  else
    printf("Press:- ");
  
  printf("Name : %s", SDL_GetKeyName(key->keysym.sym));
}