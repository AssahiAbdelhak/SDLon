# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>

  int main(int argc, char ** argv) {
    // Le p o i n t e u r vers la fenetre
    SDL_Window * pWindow = NULL;
    // Le p o i n t e u r vers la surface incluse dans la fenetre
    SDL_Surface * nouvellePartie = NULL,* chargerPartie = NULL,* chargerPatch = NULL, * image = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Rect npDestRect,cpDestRect,cptDestRect , nouvellePartieRect , chargerPartieRect , chargerPatchRect ;
    // Le p o i n t e u r vers notre police
    TTF_Font * police = NULL;
    // Une v a r i a b l e de couleur noire
    SDL_Color couleurNoire = {
      0,
      0,
      0
    };
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
    const int HEIGHT = 840,WIDTH = 1280;
    /* C r e a t i o n de la fenetre */
    pWindow = SDL_CreateWindow(" Hello World SDL2 ", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!pWindow) {
      fprintf(stderr, " Erreur a la creation de la fenetre : %s \n ", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
      fprintf(stderr, " Erreur a la creation du renderer \n ");
      exit(EXIT_FAILURE);
    }
    if ((police = TTF_OpenFont("OpenSans-Bold.ttf", 20)) == NULL) {
      fprintf(stderr, " erreur chargement font \n ");
      exit(EXIT_FAILURE);
    }
    nouvellePartie = TTF_RenderUTF8_Blended(police, " Nouvelle Partie ", couleurNoire);
    chargerPartie = TTF_RenderUTF8_Blended(police, " Charger Partie ", couleurNoire);
    chargerPatch = TTF_RenderUTF8_Blended(police, " Charger Patch ", couleurNoire);
    if (!chargerPartie) {
      fprintf(stderr, " Erreur a la creation du texte : %s\n ", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    if (!chargerPatch) {
      fprintf(stderr, " Erreur a la creation du texte : %s\n ", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    if (!nouvellePartie) {
      fprintf(stderr, " Erreur a la creation du texte : %s\n ", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Texture * nouvellePartieText = SDL_CreateTextureFromSurface(renderer, nouvellePartie);
    if (!nouvellePartieText) {
      fprintf(stderr, " Erreur a la creation du rendu du texte : %s \n ", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    SDL_Texture * chargerPartieText = SDL_CreateTextureFromSurface(renderer, chargerPartie);
    if (!chargerPartieText) {
      fprintf(stderr, " Erreur a la creation du rendu du texte : %s \n ", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    SDL_Texture * chargerPatchText = SDL_CreateTextureFromSurface(renderer, chargerPatch);
    if (!chargerPatchText) {
      fprintf(stderr, " Erreur a la creation du rendu du texte : %s \n ", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(nouvellePartie); /* on a la texture , plus besoin du texte */
    SDL_FreeSurface(chargerPartie); /* on a la texture , plus besoin du texte */
    SDL_FreeSurface(chargerPatch); /* on a la texture , plus besoin du texte */
    /* P o s i t i o n ou sera mis le texte dans la fenetre */
    // load sample . png into image
    SDL_Point mousePosition;
    SDL_QueryTexture ( nouvellePartieText , NULL , NULL , &( cpDestRect.w), &( cpDestRect.h ));
    cptDestRect.x=npDestRect.x=cpDestRect.x = (WIDTH - cpDestRect.w) / 2;
    
    cptDestRect.h=npDestRect.h=cpDestRect.h;
    cptDestRect.w=npDestRect.w=cpDestRect.w;
    npDestRect.y = (HEIGHT - 5*npDestRect.h)/2;
    cpDestRect.y = npDestRect.y + npDestRect.h*2;
    cptDestRect.y = cpDestRect.y + npDestRect.h*2;
    if (pWindow) {
      int running = 1;
      while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_MOUSEBUTTONUP:
                mousePosition.x = e.motion.x; 
                mousePosition.y = e.motion.y;

                if (SDL_PointInRect(&mousePosition, &cpDestRect)) {
                    printf("T'as clique sur charger partie\n");
                    SDL_DestroyTexture(chargerPartieText)
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderClear(renderer);
                }
                if (SDL_PointInRect(&mousePosition, &npDestRect)) {
                    printf("T'as clique sur nouvelle partie\n");
                }
                if (SDL_PointInRect(&mousePosition, &cptDestRect)) {
                    printf("T'as clique sur charger patch\n");
                }

                break;

          case SDL_QUIT:
            running = 0;
            break;
          case SDL_WINDOWEVENT:
            switch (e.window.event) {
            case SDL_WINDOWEVENT_EXPOSED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SHOWN:
              /* Le fond de la fenetre sera blanc */
              SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
              SDL_RenderClear(renderer);
              /* Ajout du texte en noir */
              SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
              
              
              SDL_RenderCopy(renderer, nouvellePartieText, NULL, & npDestRect);
              SDL_RenderDrawRect(renderer, &npDestRect);
              SDL_RenderCopy(renderer, chargerPartieText, NULL, & cpDestRect);
              SDL_RenderDrawRect(renderer, &cpDestRect);
              SDL_RenderCopy(renderer, chargerPatchText, NULL, & cptDestRect);
              SDL_RenderDrawRect(renderer, &cptDestRect);
              /* Ajout de la seconde image a une c e r t a i n e p o s i t i o n */
              /* On fait le rendu ! */
              SDL_RenderPresent(renderer);
              break;
            }
            break;
          }
        }
      }
    } else {
      fprintf(stderr, " Erreur de creation de la fenetre : %s \n ", SDL_GetError());
    }
    // D e s t r u c t i o n de la fenetre
    SDL_DestroyWindow(pWindow);
    TTF_CloseFont(police); /* Doit etre avant T T F _ Q u i t () */
    TTF_Quit();
    SDL_Quit();
    return 0;
  }