# include <stdio.h>
# include <string.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include "../lib/lib_sdl_facile.h"
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
			    SDL_WINDOW_SHOWN); /* Additional flag(s) */

  /* Check de la fenetre si elle a bien ete cree; si non, exit le programme */
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);


  //VARIABLE CINEMATIQUE

  int clefbas = 0 ;
  int test_cond = 0 ;
  int cadenas = true;
  int HoF = 0;

  // VARIABLE INPUT TEXT

    
  TTF_Font * font = TTF_OpenFont("RosesareFF0000.ttf", 12);
  SDL_Color white = {255, 255, 255, 0};
  SDL_Surface * temp = TTF_RenderText_Solid(font, "Hello", white);
  SDL_Texture * textImage = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_Rect pos = {100, 600, 50, 12};
  SDL_FreeSurface(temp);
  temp = NULL;

  SDL_StartTextInput();
  char * textInput;

  while (!quit){
    SDL_WaitEvent(&event);

    //CINEMATIQUE DE DEBUT DE JEU
    //Initialisation des variables de ma cinématique

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

    SDL_Texture * txthomme;
    SDL_Texture * txtfemme;
    
    SDL_Texture * txthomme2;
    SDL_Texture * txtfemme2;

    if(cadenas == true && clefbas < 6){
      switch(clefbas){
        case 0 :
          //img et txt crée et reste tant que aucune touche n'est press
          blackscreen(renderer);

          img = print_image(renderer, "../img/asset/trfront.png", 540, 320, 200, 200);
          txt = print_text(renderer, "RosesareFF0000.ttf", "Bonjour dresseur, je suis le professeur SDLon, mon nom est Ange.", MARGE, LIGNE1, 255, 255, 255);

          break;    
        case 1 :
          
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            SDL_DestroyTexture(txt);
            SDL_DestroyTexture(img);

            blackscreen(renderer);

          }
          test_cond = 0;

          img2 = print_image(renderer, "../img/asset/trfront.png", 540, 320, 200, 200);
          txt2 = print_text(renderer, "RosesareFF0000.ttf", "Si tu est ici c'est que tu comptes attraper des SDLon je suppose.", MARGE, LIGNE1, 255, 255, 255);

          break;
        case 2 :
          
          if(test_cond == 1){
            //detruit les images lorsque une touche est press
            SDL_DestroyTexture(txt2);
            SDL_DestroyTexture(img2);

            blackscreen(renderer);
          }
          test_cond = 0;
          
          img3 = print_image(renderer, "../img/asset/trfront.png", 540, 320, 200, 200);
          img3_2 = print_image(renderer, "../img/asset/667s.png", 450, 355, 200, 200);
          txt3 = print_text(renderer, "RosesareFF0000.ttf", "Tres bien, vois tu, ceci est un sdlon !", MARGE, LIGNE1, 255, 255, 255);

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

          img4 = print_image(renderer, "../img/asset/trfront.png", 540, 320, 200, 200);
          img4_2 = print_image(renderer, "../img/asset/667s.png", 450, 355, 200, 200);
          txt4 = print_text(renderer, "RosesareFF0000.ttf", "Tout d'abord j'ai une question.", MARGE, LIGNE1, 255, 255, 255);
          txt4_2 = print_text(renderer, "RosesareFF0000.ttf", "Est-tu un homme ou une femme ?", MARGE, LIGNE2, 255, 255, 255);

          //display du choix de sexe avec changement de couleur
          txthomme = print_text(renderer, "RosesareFF0000.ttf", "homme", 400, 100, 255, 255, 255);
          txtfemme = print_text(renderer, "RosesareFF0000.ttf", "femme", 800, 100, 255, 255, 255);

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

          img5 = print_image(renderer, "../img/asset/trfront.png", 540, 320, 200, 200);
          img5_2 = print_image(renderer, "../img/asset/667s.png", 450, 355, 200, 200);
  //      txt4 = print_text(renderer, "RosesareFF0000.ttf", "/                                                                      /", 100, 700);  taille de texte max = 72 caractères
          txt5 = print_text(renderer, "RosesareFF0000.ttf", "Tres bien, et rappelle moi comment t'appelles tu deja ?", 100, 700, 255, 255, 255);
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

          img6 = print_image(renderer, "../img/asset/trfront.png", 540, 320, 200, 200);
          img6_2 = print_image(renderer, "../img/asset/667s.png", 450, 355, 200, 200);
          txt6 = print_text(renderer, "RosesareFF0000.ttf", "Tres bien, n'oublie pas de passer me voir au labo, j'ai quelques choses", MARGE, LIGNE1, 255, 255, 255);
          txt6_2 = print_text(renderer, "RosesareFF0000.ttf", "a te donner a toi et ton ami ... , je te souhaite une bonne aventure", MARGE, LIGNE2, 255, 255, 255);
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


    affichage(renderer);

    while(SDL_PollEvent(&event)){
      switch(event.type){
        
        case SDL_KEYUP :
          PrintKeyInfo(&event.key);
          printf("Key release detected\n");
          printf("\n");
          break;
        
        case SDL_KEYDOWN :
          switch( event.key.keysym.sym ){
                
            //Choisi d'etre un homme
            case SDLK_LEFT:
              if(clefbas == 3){
                txthomme2 = print_text(renderer, "RosesareFF0000.ttf", "homme", 400, 100, 0, 0, 255);
                txtfemme = print_text(renderer, "RosesareFF0000.ttf", "femme", 800, 100, 255, 255, 255);
                HoF=0;
              }
              break;

            //Choisi d'etre une femme
            case SDLK_RIGHT:
              if(clefbas == 3){
                txtfemme2 = print_text(renderer, "RosesareFF0000.ttf", "femme", 800, 100, 0, 0, 255);
                txthomme = print_text(renderer, "RosesareFF0000.ttf", "homme", 400, 100, 255, 255, 255);
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
                SDL_DestroyTexture(txthomme);
                SDL_DestroyTexture(txthomme2);
                SDL_DestroyTexture(txtfemme);
                SDL_DestroyTexture(txtfemme2);
              }
              break;
          }

        case SDL_TEXTINPUT:
        //Special text input event
        // Only append the input if there is enough room in the buffer
          if (strlen(textInput) + strlen(event.text.text) < 20) {
            strcat(textInput, event.text.text);
            
            if (textImage) {
                SDL_DestroyTexture(textImage);
                textImage = NULL;
            }
            
            // Create a temporary surface with the text input
            SDL_Surface* temp = TTF_RenderText_Solid(font, textInput, white);
            
            if (temp) {
                // Create a texture from the surface
                textImage = SDL_CreateTextureFromSurface(renderer, temp);
                pos.w = temp->w;
                pos.h = temp->h;
                SDL_FreeSurface(temp);
                temp = NULL;
            }
          
          }


        //fin de la cinématique
        case SDL_QUIT : 
          quit = true;
          break;
        
      }
    }
  }

  /* Pause tous les SDL sous systemes pour un nombre variables de millisecondes */
  SDL_Delay(DELAY);

  /* Free la memoire */
  SDL_DestroyWindow(window);
  
  SDL_DestroyRenderer(renderer);

  SDL_StopTextInput();

  /* Eteint tous les SDL sous systemes */
  SDL_Quit();
  return 0;
}


/*
if(SDL_KEYUP == event.type){
        PrintKeyInfo(&event.key);
        printf("Key release detected\n");
        printf("\n");
      }
      else if(SDL_KEYDOWN == event.type){
        PrintKeyInfo(&event.key);
        printf("moi Key press detected\n");
        clefbas++ ;
        printf("moi clef_bas -> %d\n", clefbas);
        test_cond = 1 ;
        printf("moi test_cond -> %d\n", test_cond);
        cadenas = true ;
        printf("moi cadenas -> %d\n", cadenas);
        printf("\n");
      }
      else if(SDL_MOUSEMOTION == event.type){
        int x, y;
        mousePosition.x = event.motion.x; 
        mousePosition.y = event.motion.y;
        SDL_GetMouseState(&x,&y);
        printf("-----------%d %d-------------\n", x, y);
        
        if(clefbas == 3){
          if(SDL_PointInRect(&mousePosition, &rectH)){
            printf("JE SUIS LA C BON");
            txthomme2 = print_text(renderer, "RosesareFF0000.ttf", "homme", 400, 100, 0, 0, 255);
          }
          else if(SDL_PointInRect(&mousePosition, &rectF)){
            printf("JE SUIS LA C BON");
            txtfemme2 = print_text(renderer, "RosesareFF0000.ttf", "femme", 800, 100, 0, 0, 255);
          }
        }
      }
      else if(SDL_QUIT == event.type){ 
        quit = true;
        break;
      }
*/