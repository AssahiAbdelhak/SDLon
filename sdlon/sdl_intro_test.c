# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include "./lib/lib_sdl_facile.h"
/**
  \file sdl_prog_test.c
  \brief Programme de test sur la cinematique de debut de jeu
  \author Lilian Colla
  \version 2.0
  \date 09/02/2023
*/

int main(int argc, char **argv){
  /* Initialise les data de notre jeu*/
  SDL_Window *window = NULL;
  int quit = false;
  SDL_Event event;
  
  /*
  * Initialise le systeme video sdl (ainsi que le sous systeme lie au evenements).
  * Retourne 0 on utilise SDL_GetError() pour retourner une erreur ou un succes.
  */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  /* Cree la fenetre SDL */
  window = SDL_CreateWindow("SDLON", /* Titre de la fenetre */
			    SDL_WINDOWPOS_UNDEFINED, /* Position x de la fenetre */
			    SDL_WINDOWPOS_UNDEFINED, /* Position y de la fenetre */
			    WIDTH, /* largeur de la fenetre en pixels */
			    HEIGHT, /* hauteur de la fenetre en pixels */
			    0); /* Additional flag(s) */

  /* Check de la fenetre si elle a bien ete cree; si non, exit le programme */
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

  //VARIABLE FRAMERATE
  const int FPS = 60 ;
  const int frameDelay = 1000 / FPS ;

  Uint32 frameStart ;
  int frameTime ;

  //VARIABLE CINEMATIQUE
  int cpt = 0 ;
  int clefbas = 0 ;
  int test_cond = 0 ;
  int cadenas = true;
  while (!quit){
    SDL_WaitEvent(&event);

    frameStart = SDL_GetTicks();




    //CINEMATIQUE DE DEBUT DE JEU




    SDL_Texture * img ;
    SDL_Texture * txt ; //72 caractères maximum par lignes (espace inclu)

    SDL_Texture * img2 ;
    SDL_Texture * txt2 ;

    SDL_Texture * img3 ;
    SDL_Texture * img3_2 ;
    SDL_Texture * txt3 ;

    SDL_Texture * img4 ;
    SDL_Texture * img4_2 ;
    SDL_Texture * txt4 ;
    SDL_Texture * txt4_2 ;

    SDL_Texture * img5 ;
    SDL_Texture * img5_2 ;
    SDL_Texture * txt5 ;

    SDL_Texture * img6 ;
    SDL_Texture * img6_2 ;
    SDL_Texture * txt6 ;
    SDL_Texture * txt6_2 ;

    if(cadenas == true && clefbas < 6){
      switch(clefbas){
        case 0 :
          //img et txt crée et reste tant que aucune touche n'est press
          blackscreen(renderer);

          img = print_image(renderer, "./img/asset/trfront.png", 540, 320, 200, 200);
          txt = print_text(renderer, "RosesareFF0000.ttf", "Bonjour dresseur, je suis le professeur SDLon, mon nom est Ange.", MARGE, LIGNE1);

          break;    
        case 1 :
          
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            SDL_DestroyTexture(txt);
            SDL_DestroyTexture(img);

            blackscreen(renderer);

          }
          test_cond = 0;

          img2 = print_image(renderer, "./img/asset/trfront.png", 540, 320, 200, 200);
          txt2 = print_text(renderer, "RosesareFF0000.ttf", "Si tu est ici c'est que tu comptes attraper des SDLon je suppose.", MARGE, LIGNE1);

          break;
        case 2 :
          
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            SDL_DestroyTexture(txt2);
            SDL_DestroyTexture(img2);

            blackscreen(renderer);
          }
          test_cond = 0;
          
          img3 = print_image(renderer, "./img/asset/trfront.png", 540, 320, 200, 200);
          img3_2 = print_image(renderer, "./img/asset/667s.png", 450, 355, 200, 200);
          txt3 = print_text(renderer, "RosesareFF0000.ttf", "Tres bien, vois tu, ceci est un sdlon !", MARGE, LIGNE1);

          break;
        case 3 :
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            SDL_DestroyTexture(txt3);
            SDL_DestroyTexture(img3);
            SDL_DestroyTexture(img3_2);

            blackscreen(renderer);
          }
          test_cond = 0;

          img4 = print_image(renderer, "./img/asset/trfront.png", 540, 320, 200, 200);
          img4_2 = print_image(renderer, "./img/asset/667s.png", 450, 355, 200, 200);
          txt4 = print_text(renderer, "RosesareFF0000.ttf", "Tout d'abord j'ai une question.", MARGE, LIGNE1);
          txt4_2 = print_text(renderer, "RosesareFF0000.ttf", "Est-tu un homme ou une femme ?", MARGE, LIGNE2);
          //voir programme de abdelhak pour créer un choix via l'écran et sauvegarder la valeur dans le jeu ou un fichier annexe.
          break;
        case 4 :
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            SDL_DestroyTexture(txt4);
            SDL_DestroyTexture(txt4_2);
            SDL_DestroyTexture(img4);
            SDL_DestroyTexture(img4_2);

            blackscreen(renderer);
          }
          test_cond = 0;

          img5 = print_image(renderer, "./img/asset/trfront.png", 540, 320, 200, 200);
          img5_2 = print_image(renderer, "./img/asset/667s.png", 450, 355, 200, 200);
  //      txt4 = print_text(renderer, "RosesareFF0000.ttf", "/                                                                      /", 100, 700);  taille de texte max = 72 caractères
          txt5 = print_text(renderer, "RosesareFF0000.ttf", "Tres bien, et rappelle moi comment t'appelles tu deja ?", 100, 700);
          // voir prog de abdelhak pour écrire dans le jeu et sauvegarder la valeur dans le jeu ou un fichier annexe
          break;
        case 5 :
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            SDL_DestroyTexture(txt5);
            SDL_DestroyTexture(img5);
            SDL_DestroyTexture(img5_2);

            blackscreen(renderer);
          }
          test_cond = 0;

          img6 = print_image(renderer, "./img/asset/trfront.png", 540, 320, 200, 200);
          img6_2 = print_image(renderer, "./img/asset/667s.png", 450, 355, 200, 200);
          txt6 = print_text(renderer, "RosesareFF0000.ttf", "Tres bien, n'oublie pas de passer me voir au labo, j'ai quelques choses", MARGE, LIGNE1);
          txt6_2 = print_text(renderer, "RosesareFF0000.ttf", "a te donner a toi et ton ami ... , je te souhaite une bonne aventure", MARGE, LIGNE2);
          //voir programme de abdelhak pour créer un choix via l'écran et sauvegarder la valeur dans le jeu ou un fichier annexe.
          break;
        case 6 :
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            SDL_DestroyTexture(txt6);
            SDL_DestroyTexture(txt6_2);
            SDL_DestroyTexture(img6);
            SDL_DestroyTexture(img6_2);

            blackscreen(renderer);
          }
          test_cond = 0;
          break;
        default:
          blackscreen(renderer);
          break;
      }
    }
    cadenas = false ;


    // /!\ FIN DE CINEMATIQUE




    //Barre de texte -> attente d'action
    //se termine a la fin de la cinematique /!\ BUG ICI JE PENSE.
    if(clefbas < 6){
      
      SDL_Surface * surfbarre ;
      SDL_Texture * barre ;
      if(cpt==0){
        SDL_Rect rect = {WIDTH-100, 700, 1, 20};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        surfbarre = SDL_CreateRGBSurface(0,1,20,32,0,0,0,0);
        SDL_RenderDrawRect(renderer, &rect);
        barre = SDL_CreateTextureFromSurface(renderer, surfbarre);
        SDL_RenderCopy(renderer, barre, &rect, NULL);
      }
      if(cpt>10){
        if(cpt==11){
          SDL_Rect rect = {WIDTH-100, 700, 1, 20};
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
          surfbarre = SDL_CreateRGBSurface(0,1,20,32,0,0,0,0);
          SDL_RenderDrawRect(renderer, &rect);
          barre = SDL_CreateTextureFromSurface(renderer, surfbarre);
          SDL_RenderCopy(renderer, barre, &rect, NULL);
        }
      }
      if(cpt == 20){
        cpt = 0;
      }
      else{
        cpt++;
      }
    }

    affichage(renderer);
    
    //FRAMERATE

    frameTime = SDL_GetTicks() - frameStart;
    if(frameDelay > frameTime)
      SDL_Delay(frameDelay - frameTime); 
    //-----------

    switch (event.type){
      case SDL_KEYUP:
        PrintKeyInfo(&event.key);
        printf("Key release detected\n");
        printf("\n");
        break;
      case SDL_KEYDOWN:
        PrintKeyInfo(&event.key);
        printf("Key press detected\n");
        clefbas++ ;
        printf("clef_bas -> %d\n", clefbas);
        test_cond = 1 ;
        printf("test_cond -> %d\n", test_cond);
        cadenas = true ;
        printf("cadenas -> %d\n", cadenas);
        printf("\n");
        break;
      case SDL_QUIT: 
        quit = true;
        break;
      default:      //ici SDL_MOUSEMOTION   /!\ c'est un problème à régler
        cpt++;
        printf("clef_bas -> %d\n", clefbas);
        printf("test_cond -> %d\n", test_cond);
        printf("cadenas -> %d\n", cadenas);
        printf("\n");
        break;
    }
  }

  /* Pause tous les SDL sous systemes pour un nombre variables de millisecondes */
  SDL_Delay(DELAY);

  /* Free la memoire */
  SDL_DestroyWindow(window);
  
  SDL_DestroyRenderer(renderer);

  /* Eteint tous les SDL sous systemes */
  SDL_Quit();
  return 0;
}
