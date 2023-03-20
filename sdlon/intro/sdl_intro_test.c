# include <stdio.h>
# include <string.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include "../lib/lib_sdl_facile.h"
#include "../map.h"
/**
  \file sdl_prog_test.c
  \brief Programme de test sur la cinematique de debut de jeu
  \author Lilian Colla
  \version 2.0
  \date 09/02/2023
*/


void afficherCinematique(SDL_Window * window,SDL_Surface *screen){
  /* Initialise les data de notre jeu*/
  //SDL_Window *window = NULL;
  int quit = false;
  SDL_Event event;
  SDL_Log("je suis passer par la\n");
  /*
  * Initialise le systeme video sdl (ainsi que le sous systeme lie au evenements).
  * Retourne 0 on utilise SDL_GetError() pour retourner une erreur ou un succes.
  */
 /*Je vais commenter ce code puisque je l'ai deja initialise dans mon program*/
  /*if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
    return 1;
  }*/

  /* Cree la fenetre SDL */
  
  //window = SDL_CreateWindow("SDLON", /* Titre de la fenetre */
		//	    SDL_WINDOWPOS_UNDEFINED, /* Position x de la fenetre */
			//    SDL_WINDOWPOS_UNDEFINED, /* Position y de la fenetre */
			//    WIDTH, /* largeur de la fenetre en pixels */
			  //  HEIGHT, /* hauteur de la fenetre en pixels */
			    //SDL_WINDOW_SHOWN); /* Additional flag(s) */

  /* Check de la fenetre si elle a bien ete cree; si non, exit le programme */
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 1;
  }
  //SDL_Surface * screen = SDL_GetWindowSurface(window);


  //VARIABLE CINEMATIQUE

  int clefbas = 0 ;
  int test_cond = 0 ;
  int cadenas = true;
  int HoF = 0;

  while (!quit){
    SDL_WaitEvent(&event);

    //CINEMATIQUE DE DEBUT DE JEU
    //Initialisation des variables de ma cinématique
/*
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
    SDL_Texture * txt5_2 ;

    SDL_Texture * txthomme;
    SDL_Texture * txtfemme;
    
    SDL_Texture * txthomme2;
    SDL_Texture * txtfemme2;
*/
    if(cadenas == true && clefbas < 6){
      switch(clefbas){
        case 0 :
          //img et txt crée et reste tant que aucune touche n'est press
          blackscreen(screen);
          SDL_Log("et par la\n");
          //Uint32 black = 0x000;
          //SDL_FillRect(items_surface,&rect_arrow,black);
          
          print_image(screen, "img/asset/SDLon_character/trfront.png", 540, 320, 200, 200);
          SDL_Log("et par la 1\n");
          print_text(screen, "RosesareFF0000.ttf", "Bonjour dresseur, je suis le professeur SDLon, mon nom est Ange.", MARGE, LIGNE1, 255, 255, 255);
          SDL_Log("et par la 2\n");
          affichage(window);
          SDL_Log("error here ?\n");
          break;    
        case 1 :
          
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            /*SDL_DestroyTexture(txt);
            SDL_DestroyTexture(img);*/

            blackscreen(screen);
affichage(window);
          }
          test_cond = 0;

          print_image(screen, "img/asset/SDLon_character/trfront.png", 540, 320, 200, 200);
          print_text(screen, "RosesareFF0000.ttf", "Si tu est ici c'est que tu comptes attraper des SDLon je suppose.", MARGE, LIGNE1, 255, 255, 255);
affichage(window);
          break;
        case 2 :
          
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            /*SDL_DestroyTexture(txt2);
            SDL_DestroyTexture(img2);
*/
            blackscreen(screen);
            affichage(window);
          }
          test_cond = 0;
          
          print_image(screen, "img/asset/SDLon_character/trfront.png", 540, 320, 200, 200);
          print_image(screen, "img/asset/SDLon_creature/667s.png", 450, 355, 200, 200);
          print_text(screen, "RosesareFF0000.ttf", "Tres bien, vois tu, ceci est un sdlon !", MARGE, LIGNE1, 255, 255, 255);
affichage(window);
          break;
        case 3 :
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            /*SDL_DestroyTexture(txt3);
            SDL_DestroyTexture(img3);
            SDL_DestroyTexture(img3_2);*/

            blackscreen(screen);
            affichage(window);
          }
          test_cond = 0;

          print_image(screen, "img/asset/SDLon_character/trfront.png", 540, 320, 200, 200);
          print_image(screen, "img/asset/SDLon_creature/667s.png", 450, 355, 200, 200);
          print_text(screen, "RosesareFF0000.ttf", "Tout d'abord j'ai une question.", MARGE, LIGNE1, 255, 255, 255);
          print_text(screen, "RosesareFF0000.ttf", "Est-tu un homme ou une femme ?", MARGE, LIGNE2, 255, 255, 255);

          //display du choix de sexe avec changement de couleur
          print_text(screen, "RosesareFF0000.ttf", "homme", 400, 100, 255, 255, 255);
          print_text(screen, "RosesareFF0000.ttf", "femme", 800, 100, 255, 255, 255);
affichage(window);
          break;
        
        case 4 :
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            /*SDL_DestroyTexture(txt4);
            SDL_DestroyTexture(txt4_2);
            SDL_DestroyTexture(img4);
            SDL_DestroyTexture(img4_2);
*/
            blackscreen(screen);
            affichage(window);
          }
          test_cond = 0;

          print_image(screen, "img/asset/SDLon_character/trfront.png", 540, 320, 200, 200);
          print_image(screen, "img/asset/SDLon_creature/667s.png", 450, 355, 200, 200);
          print_text(screen, "RosesareFF0000.ttf", "Tres bien, n'oublie pas de passer me voir au labo, j'ai quelques choses", MARGE, LIGNE1, 255, 255, 255);
          print_text(screen, "RosesareFF0000.ttf", "a te donner, je te souhaite une bonne aventure", MARGE, LIGNE2, 255, 255, 255);
          affichage(window);
          //voir programme de abdelhak pour créer un choix via l'écran et sauvegarder la valeur dans le jeu ou un fichier annexe.
          break;
        case 5 :
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            /*SDL_DestroyTexture(txt5);
            SDL_DestroyTexture(txt5_2);
            SDL_DestroyTexture(img5);
            SDL_DestroyTexture(img5_2);
*/
            blackscreen(screen);
            printMap(window,screen);
            affichage(window);
            return ;
          }
          test_cond = 0;
          break;
        default:
          blackscreen(screen);
          affichage(window);
          break;
      }
    }
    cadenas = false ;


    // /!\ FIN DE CINEMATIQUE


    affichage(window);


    switch(event.type){
      
      case SDL_KEYUP :
        PrintKeyInfo(&event.key);
        printf("Key release detected\n");
        printf("\n");
        break;
      
      case SDL_KEYDOWN :
        switch( event.key.keysym.sym ){
              
          //    <!> obliger de choisir sinon segmentation fault (si on fait espace sans avoir choisi avec les flèche le programme plante).   
          //Choisi d'etre un homme
          case SDLK_LEFT:
            if(clefbas == 3){
              print_text(screen, "RosesareFF0000.ttf", "homme", 400, 100, 0, 0, 255);
              print_text(screen, "RosesareFF0000.ttf", "femme", 800, 100, 255, 255, 255);
              HoF=0;
            }
            break;

          //Choisi d'etre une femme
          case SDLK_RIGHT:
            if(clefbas == 3){
              print_text(screen, "RosesareFF0000.ttf", "femme", 800, 100, 0, 0, 255);
              print_text(screen, "RosesareFF0000.ttf", "homme", 400, 100, 255, 255, 255);
              HoF=1;
            }
            break;
          //passe a la suite de la cinematique avec la reference du sexe choisi dans la variable HoF(Homme ou Femme)

          case SDLK_SPACE:

            PrintKeyInfo(&event.key);
            printf("moi Key press detected\n");
            clefbas++ ;
            printf("moi clef_bas -> %d\n", clefbas);
            test_cond = 1 ;
            printf("moi test_cond -> %d\n", test_cond);
            cadenas = true ;
            printf("moi cadenas -> %d\n", cadenas);
            printf("\n");
            if(clefbas == 4){
              /*SDL_DestroyTexture(txthomme);
              SDL_DestroyTexture(txthomme2);
              SDL_DestroyTexture(txtfemme);
              SDL_DestroyTexture(txtfemme2);*/
            }
            break;
            
        }
        break;

        //fin de la cinématique
        case SDL_QUIT : 
          quit = true;
          break;

        default:
          if(clefbas == 5)
            quit = true;
          break;
        
      }
    
  }

  /* Pause tous les SDL sous systemes pour un nombre variables de millisecondes */
  SDL_Delay(DELAY);

  /* Free la memoire */
  //pareil la
  //SDL_DestroyWindow(window);
  
  //SDL_DestroyRenderer(renderer);

  SDL_StopTextInput();

  /* Eteint tous les SDL sous systemes */
  SDL_Quit();
  return 0;
}

