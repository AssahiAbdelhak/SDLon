# include <stdio.h>
#include <string.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <dirent.h>

#define HEIGHT 840
#define WIDTH  1280

/*
cd C:\Users\bdalh\Desktop\test
gcc sdl_test.c -IC:\Users\bdalh\Desktop\developpement\x86_64-w64-mingw32\include -LC:\Users\bdalh\Desktop\developpement\x86_64-w64-mingw32\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lexpat -o prog
*/


/*
A faire : 
creer des layers sur tiled
extraire ma nuellement les valeur avec le tileset utilise 
les affecter a une structure
faire boucle sur chaque layer 
        faire boucle sur chaque tile afficher le tile
*/



#define MAX_LAYERS 100

int tile_width, tile_height;
int num_layers = 0;
int tile_ids[MAX_LAYERS][1024][1024];
int num_tiles_x, num_tiles_y;
SDL_Texture *tileset_texture;
int tileset_width, tileset_height;
SDL_Window *window;
SDL_Renderer *renderer;
int window_width, window_height;
/*
void start_element_handler(void *data, const char *element_name, const char **attributes)
{
    if (strcmp(element_name, "map") == 0) {
        printf("%d\t%d\t%d\t%d\n",atoi(attributes[1]),atoi(attributes[2]),atoi(attributes[3]),atoi(attributes[4]));
        exit(1);
        tile_width = atoi(attributes[2]);
        tile_height = atoi(attributes[3]);
        num_tiles_x = atoi(attributes[0]);
        num_tiles_y = atoi(attributes[1]);
    } else if (strcmp(element_name, "layer") == 0) {
        num_layers++;
    } else if (strcmp(element_name, "data") == 0) {
        int layer = num_layers - 1;
        int i = 0, j = 0;
        const char *data = attributes[0];
        char *token = strtok((char *)data, ",");
        while (token != NULL) {
            int tile_id = atoi(token);
            tile_ids[layer][j][i] = tile_id;
            i++;
            if (i == num_tiles_x) {
                i = 0;
                j++;
            }
            token = strtok(NULL, ",");
        }
    } else if (strcmp(element_name, "tileset") == 0) {
        const char *tileset_filename = attributes[0];
        char tileset_path[256];
        sprintf(tileset_path, "assets/%s", tileset_filename);
        SDL_Surface *tileset_surface = IMG_Load(tileset_path);
        tileset_texture = SDL_CreateTextureFromSurface(renderer, tileset_surface);
        tileset_width = tileset_surface->w;
        tileset_height = tileset_surface->h;
        SDL_FreeSurface(tileset_surface);
    }
}

void render_tile(int tile_id, int x, int y)
{
    if (tile_id == 0) {
        return;
    }

    tile_id--;
    int tile_x = tile_id % (tileset_width / tile_width);
    int tile_y = tile_id / (tileset_width / tile_width);
    SDL_Rect src_rect = {tile_x * tile_width, tile_y * tile_height, tile_width, tile_height};
    SDL_Rect dst_rect = {x, y, tile_width, tile_height};
    SDL_RenderCopy(renderer, tileset_texture, &src_rect, &dst_rect);
}

void render_layer(int layer)
{
    for (int y = 0; y < num_tiles_y; y++) {
        for (int x = 0; x < num_tiles_x; x++) {
            int tile_id = tile_ids[layer][y][x];
            int screen_x = x * tile_width;
            int screen_y = y * tile_height;
            render_tile(tile_id, screen_x, screen_y);
        }
    }
}

void render_all_layers()
{
    for (int layer = 0; layer < num_layers; layer++) {
        render_layer(layer);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <tmx_file>\n", argv[0]);
    }

    char *tmx_filename = argv[1];
    FILE *tmx_file = fopen(tmx_filename, "r");

    if (tmx_file == NULL) {
        printf("Error: could not open file %s\n", tmx_filename);
        return 1;
    }

    fseek(tmx_file, 0L, SEEK_END);
    long tmx_file_size = ftell(tmx_file);
    fseek(tmx_file, 0L, SEEK_SET);
    char *tmx_contents = malloc(tmx_file_size);
    fread(tmx_contents, 1, tmx_file_size, tmx_file);
    fclose(tmx_file);

    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element_handler, NULL);
    XML_Parse(parser, tmx_contents, tmx_file_size, 1);
    XML_ParserFree(parser);
    free(tmx_contents);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error: could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    window_width = num_tiles_x * tile_width;
    window_height = num_tiles_y * tile_height;
    window = SDL_CreateWindow("Tiled Map Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Error: could not create SDL window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Error: could not create SDL renderer: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    render_all_layers();

    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyTexture(tileset_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

*/















void showPlayerInMap(SDL_Window *pWindow,SDL_Surface *screen){
  /*SDL_Surface * map = IMG_Load("images/map_villeA.png");
  SDL_Surface * personnage = IMG_Load("images/personnage.png");
  SDL_Rect rect,persRect = {500,500,98,76};
  rect.x = -200;
  rect.y = -200;
  rect.h = 10000;
  rect.w = 2395;
  int x=-200;
  int y=-200;
  SDL_BlitSurface(map,NULL,screen,&rect);
  SDL_BlitSurface(personnage,NULL,screen,&persRect);
  SDL_UpdateWindowSurface(pWindow);
*/
    SDL_Surface * tile = IMG_Load("images/pokemon_style.png");
    if(!tile)
      printf("IMG_Load: %s\n", IMG_GetError());
    // handle error
    SDL_Rect rect = {0,0,16,16};
    
    int tile_x = 140;
    int tile_y = 6;
    SDL_Rect src_rect = {tile_y*16,tile_x*16, 16, 16};
    for(int i = 0 ;i < 10 ; i++){
        rect.x = 16*i;
        SDL_BlitSurface(tile,&src_rect,screen,&rect);
    }
    //SDL_BlitSurface(tile,NULL,screen,&rect);
    SDL_UpdateWindowSurface(pWindow);
  SDL_Event e;
  SDL_Point mousePosition;
  while(1){
    while(SDL_PollEvent(&e)) { 
      switch(e.type){
        case SDL_QUIT:
          destroy(pWindow,NULL);
        break;
       
      }
      }
    }

}
void afficherMenu(SDL_Window *pWindow, SDL_Surface *screen,char *menus[],int N,TTF_Font *font);
void destroy(SDL_Window *pWindow,TTF_Font *font);
void afficherLesSauvegardes(SDL_Window *pWindow,TTF_Font *font,SDL_Surface *secreen,char strings[][100],int N,SDL_Rect *rect){
  SDL_Rect rects[N];
  SDL_Color white = {255,255,255};
  int y = (HEIGHT - (50*2) - (50*N))/N;
  int x = (WIDTH -200 )/2;
  for(int i=0;i<N;i++){
    
    rects[i].y = y;
    SDL_Surface *texte = TTF_RenderUTF8_Blended(font,strings[i],white);
    rects[i].x = (WIDTH - 200 )/2;
    rects[i].h = 50;
    rects[i].w = 200;
    SDL_FillRect(secreen,&rects[i],SDL_MapRGB(secreen->format,180,180,180));
    rects[i].x = (WIDTH - texte->w )/2;
    rects[i].y += (texte->h)/2;
    SDL_BlitSurface(texte,NULL,secreen,&rects[i]);
    SDL_FreeSurface(texte);
    y+=55;
    printf("%s\n",strings[i]);
  }
  SDL_UpdateWindowSurface(pWindow);
    SDL_Event e;
  SDL_Point mousePosition;
  while(1){
    while(SDL_PollEvent(&e)) { 
      switch(e.type){
        case SDL_QUIT:
        destroy(pWindow,font);
        break;
        case SDL_MOUSEBUTTONUP:
          printf("click_n");
          mousePosition.x = e.motion.x; 
          mousePosition.y = e.motion.y;
            if (SDL_PointInRect(&mousePosition, rect)) {
              SDL_FillRect(secreen,NULL,SDL_MapRGB(secreen->format,0,0,0));
              SDL_UpdateWindowSurface(pWindow);
              char *menus[4] = {"Nouvelle Partie","Charger Partie","Charger Patch","Quitter"};
              return afficherMenu(pWindow,secreen,menus,4,font);
            } 
            break;
      }
      }
    }
  
}

void destroy(SDL_Window *pWindow,TTF_Font *font){
  SDL_DestroyWindow(pWindow);
    TTF_CloseFont(font); /* Doit etre avant T T F _ Q u i t () */
    TTF_Quit();
    SDL_Quit();
    exit(1);
}

void newSaveGame(SDL_Window *pWindow,TTF_Font *font,SDL_Surface *screen){

  SDL_Color white = {255,255,255};
  SDL_Color red = {255,0,0};
  SDL_Surface *name;
  SDL_Surface *btn = TTF_RenderUTF8_Blended(font,"Commencer",white),*retour=TTF_RenderUTF8_Blended(font,"retour",white),*error=TTF_RenderUTF8_Blended(font,"",red);
  SDL_Surface *welcomeMsg = TTF_RenderUTF8_Blended(font,"Bienvenue Sur SDLon",white);
  SDL_Surface *instrctionMsg = TTF_RenderUTF8_Blended(font,"Veuillez saisir le nom de votre sauvgarde",white);
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
      SDL_UpdateWindowSurface(pWindow);
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
          if(SDL_FillRect(name,NULL,SDL_MapRGB(name->format,0,0,0))==0)
            printf("ok\n");
          else
            printf("ko,%s\n",SDL_GetError());
          SDL_BlitSurface(name,NULL,screen,&rect);
          SDL_FreeSurface(name);
          SDL_UpdateWindowSurface(pWindow);
          printf("1Acces to index %d\n",index);
          if(index==0)
            savaGameName[index]=' ';
          else
            savaGameName[index]='\0';
          name = TTF_RenderUTF8_Blended(font,savaGameName, white);
          rect.x = (WIDTH - name->w)/2;
          printf("back space\n");
          printf("%s\n",savaGameName);
          SDL_BlitSurface(name,NULL,screen,&rect);
          SDL_FreeSurface(name);
          SDL_UpdateWindowSurface(pWindow);
          
        }
        else if(e.type== SDL_TEXTINPUT&&index<10){
          strcat(savaGameName,e.text.text);
          printf("2Acces to index %d\n",index);
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
                  
                  char path[300];
                  sprintf(path,"sauvegardes/%s.txt",savaGameName);
                  printf("%s\n",path);
                  FILE *f = fopen(path,"w");
                  if(f==NULL){
                    printf("Error cannot create this file\n");
                  }
                  fclose(f);
          
                  printf("Clear!!!!!!!!!!!!!!!!!!!");
                  SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
                  showPlayerInMap(pWindow,screen);
                }
                
              }else if (SDL_PointInRect(&mousePosition, &retourRect)) {
                printf("yeah!!!\n");
                SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
                char *menus[4] = {"Nouvelle Partie","Charger Partie","Charger Patch","Quitter"};
                return afficherMenu(pWindow,screen,menus,4,font);
              }
        }
        if(e.type==SDL_QUIT){
          running=0;
          }
      }
    }
    SDL_StopTextInput();
  destroy(pWindow,font);
  }
  
void getSaveGames(SDL_Window *pWindow,TTF_Font *font,SDL_Surface *screen){
  SDL_Rect rect;
  SDL_Color white = {255,255,255};
  SDL_Surface *title = TTF_RenderUTF8_Blended(font,"Charger Le jeu",white);
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
  d = opendir("sauvegardes");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if(strcmp(dir->d_name,".")!=0&&strcmp(dir->d_name,"..")!=0){
        strcpy(fileNames[index],dir->d_name);
        index++;
      }
        
    }
    closedir(d);
  }
  afficherLesSauvegardes(pWindow,font,screen,fileNames,index,&rect);
  SDL_Event e;
  SDL_Point mousePosition;
  while(1){
    while(SDL_PollEvent(&e)) { 
      switch(e.type){
        case SDL_QUIT:
          destroy(pWindow,font);
        break;
        case SDL_MOUSEBUTTONUP:
          mousePosition.x = e.motion.x; 
          mousePosition.y = e.motion.y;
            if (SDL_PointInRect(&mousePosition, &rect)) {
              SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
              SDL_UpdateWindowSurface(pWindow);
              char *menus[4] = {"Nouvelle Partie","Charger Partie","Charger Patch","Quitter"};
              return afficherMenu(pWindow,font,screen,4,font);
            } 
          break;
      }
      }
    }
  return destroy(pWindow,font);
}

void afficherMenu(SDL_Window *pWindow, SDL_Surface *screen,char *menus[],int N,TTF_Font *font){
    
    SDL_Surface *btns[N];
    SDL_Color colors[2] = {{255,0,0},{255,255,255}};
    SDL_Rect rects[N];
    int active[N];
    int i;
    while(1){
      for( i=0;i<N;i++){
      btns[i] = TTF_RenderUTF8_Blended(font,menus[i],colors[1]);
      /**/
      rects[i].w =200;
      rects[i].h = btns[i]->h;
      rects[i].x = (WIDTH - 200 - (btns[i]->w)/2)/2;
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
                            SDL_UpdateWindowSurface(pWindow);
                            return showPlayerInMap(pWindow,screen);
                            break;
                          case 1:
                            SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
                            SDL_UpdateWindowSurface(pWindow);
                            return getSaveGames(pWindow,font,screen);
                            break;
                          case 3:
                            return destroy(pWindow,font);
                            break;
                        }
                    }
                  }
                
                break;

          case SDL_QUIT:
            destroy(pWindow,font) ;
            break;
          }
        }
    }
  

}}

int main(int argc, char ** argv) {
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
    pWindow = SDL_CreateWindow(" Hello World SDL2 ", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN);
    if (!pWindow) {
      fprintf(stderr, " Erreur a la creation de la fenetre : %s \n ", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    
    if ((police = TTF_OpenFont("OpenSans-Bold.ttf", 20)) == NULL) {
      fprintf(stderr, " erreur chargement font \n ");
      exit(EXIT_FAILURE);
    }
    SDL_Surface * screen;
    screen = SDL_GetWindowSurface(pWindow);
    char *menus[4] = {"Nouvelle Partie","Charger Partie","Charger Patch","Quitter"};

    afficherMenu(pWindow,screen,menus,4,police);
  
    /* P o s i t i o n ou sera mis le texte dans la fenetre */
    // load sample . png into image
    if (pWindow) {
      int running = 1;
      while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_MOUSEBUTTONUP:

                
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
              /* Ajout du texte en noir */
              
              /* Ajout de la seconde image a une c e r t a i n e p o s i t i o n */
              /* On fait le rendu ! */
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
    destroy(pWindow,police);
    return 0;
  }
  