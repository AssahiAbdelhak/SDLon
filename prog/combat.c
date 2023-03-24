#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "map.h"
#include "include/sdlon_generate.h"

#define HEIGHT 840
#define WIDTH 1280

void printControlles(SDL_Window *window,SDL_Surface * screen,player_t player, sdlon sd);
void onAttack(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int width,int height,player_t player, sdlon sd);
void botton(SDL_Surface *surface,char * titre,int width,int height,int x,int y,int selected);
int afficherLeCombat(SDL_Window *window,SDL_Surface * screen,player_t player, sdlon sd);

void updateMenus(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int width,int height,int n){
    Uint32 bg = 0xae48f1;
    SDL_Rect rect = {(WIDTH - width)/2,(HEIGHT-height)/2,width,height};
    SDL_FillRect(surface,NULL,bg);
    botton(surface,"Reprendre",(width-40),80,20,30,(0==n));
    botton(surface,"Sauvegarder",(width-40),80,20,140,(1==n));
    botton(surface,"SDLons",(width-40),80,20,250,(2==n));
    botton(surface,"Sac",(width-40),80,20,360,(3==n));
    botton(surface,"Information",(width-40),80,20,470,(4==n));
    botton(surface,"Quitter",(width-40),80,20,580,(5==n));
    SDL_BlitSurface(surface,NULL,screen,&rect);
    SDL_UpdateWindowSurface(window);
}

int afficherTableauMenu(SDL_Window *window,SDL_Surface * screen,int width,int height){
    SDL_Surface *tableauMenus = SDL_CreateRGBSurface(0, width, height, 32, 0, 219, 233, 172);
    Uint32 bg = 0xdbeaa9;
    SDL_FillRect(tableauMenus,NULL,bg);
    SDL_Rect container = {0,0,height,width};
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Rect rect = {(WIDTH - width)/2,(HEIGHT-height)/2,width,height};
    SDL_Surface * copy = SDL_CreateRGBSurface(0, width, height, 32, 0, 219, 233, 172);
    SDL_BlitSurface(screen,&rect,copy,&container);
    int nb=0;
    updateMenus(window,screen,tableauMenus,width,height,nb);
    SDL_BlitSurface(tableauMenus,NULL,screen,&rect);
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
                        nb=(nb-1);
                        nb = (nb<0)?(nb + 6):(nb);
                        break;
                    case SDLK_DOWN:
                        nb=(nb+1)%6;
                        break;
                    case SDLK_RETURN:
                        SDL_Log("copy that\n");
                        SDL_BlitSurface(copy,NULL,screen,&rect);
                        SDL_UpdateWindowSurface(window);
                        return nb;
                }
                updateMenus(window,screen,tableauMenus,width,height,nb);
        }
    }
}}

void attaque_graphique(SDL_Window *window,SDL_Surface *screen,int width,int height,SDL_Surface *surface,int x,int y,char *name_attaque,int type_sdl,int selected){
    /*TODO : creer des variables pour les couleurs de haque type*/
    SDL_Surface *attaque_surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 219, 233, 172);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    Uint32 bg = 0xdbeaa9;
    Uint32 bg_selected = 0x404040;
    //penser a ajouter d'autres couleurs qui change selon le type
    Uint32 bg_feu = 0xf3582c;
    Uint32 bg_normal = 0xabaf74;
    Uint32 bg_eau = 0x6d92c2;
    Uint32 bg_terre = 0x7be23a;
    if(selected)
        SDL_FillRect(attaque_surface,NULL,bg);
    else
        SDL_FillRect(attaque_surface,NULL,bg_selected);
    SDL_Color black = {0,0,0};
    SDL_Color white = {255,255,255};
    SDL_Color red = {255,0,0};

    SDL_Surface *nom_attaque = TTF_RenderUTF8_Blended(font,name_attaque,black);
    int fixed_height_for_type=30;
    int fixed_width_for_type=60;
    SDL_Surface *type;
    SDL_Surface *type_container = SDL_CreateRGBSurface(0, fixed_width_for_type, fixed_height_for_type, 32, 0, 0, 0, 0);
    if(type_sdl==FEU){
        type = TTF_RenderUTF8_Blended(font,"Feu",white);
        SDL_FillRect(type_container,NULL,bg_feu);
    }  
    else if(type_sdl==EAU){
        type = TTF_RenderUTF8_Blended(font,"Eau",white);
        SDL_FillRect(type_container,NULL,bg_eau);
    }
    else if(type_sdl==TERRE){
        SDL_FillRect(type_container,NULL,bg_terre);
        type = TTF_RenderUTF8_Blended(font,"Terre",white);
    } 
    else if(type_sdl==AIR){
        SDL_FillRect(type_container,NULL,bg_normal);
        type = TTF_RenderUTF8_Blended(font,"Air",white);
    }
    SDL_Surface *force = TTF_RenderUTF8_Blended(font,"PP Inf",black);

    SDL_Rect rect;
    rect.h=nom_attaque->h;
    rect.w=nom_attaque->w;
    rect.y=10;
    rect.x=(width-nom_attaque->w)/2;
    SDL_BlitSurface(nom_attaque,NULL,attaque_surface,&rect);
    rect.h=type->h;
    rect.w=type->w;
    rect.y=0;
    rect.x=(60-type->w)/2;
    SDL_BlitSurface(type,NULL,type_container,&rect);
    rect.h=fixed_height_for_type;
    rect.w=fixed_width_for_type;
    rect.y=50;
    rect.x=20;
    SDL_BlitSurface(type_container,NULL,attaque_surface,&rect);
    rect.h=force->h;
    rect.w=force->w;
    rect.y=50;
    rect.x=width-(force->w) - 10;
    SDL_BlitSurface(force,NULL,attaque_surface,&rect);
    rect.h=height;
    rect.w=width;
    rect.y=y;
    rect.x=x;
    SDL_BlitSurface(attaque_surface,NULL,surface,&rect);
    SDL_UpdateWindowSurface(window);
    return;
}

void handle_events(SDL_Window *window,SDL_Surface *screen,int nb,player_t player, sdlon sd){
    switch (nb){
    case 0:
        afficherLeCombat(window,screen,player,sd);
        break;
    // à implémenter après
    default:
        afficherLeCombat(window,screen,player,sd);
        break;
    }
    return;
}

void handle_sdlons_events(SDL_Window *window,SDL_Surface *screen,int nb,player_t player, sdlon sd){
    switch (nb){
    case 0:
    case 1:
    case 2:
    case 3:
        printf("Là il faut faire qlq chose, mais por l'instant je vais revenir au combat\n");
        afficherLeCombat(window,screen,player,sd);
        break;
    case 4:
        afficherLeCombat(window,screen,player, sd);
    // à implémenter après
    default:
        break;
    }
    return;
}

void printSdlonBar(SDL_Window *window,SDL_Surface *screen,int width, int height,int x,int y,char * nom,char *gendre,int vie,int lev,int selected,char * path){
    SDL_Surface *container = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    Uint32 blue_bg = 0x69bdef;
    Uint32 bg_selected = 0xdaed9c;
    if(selected)
        SDL_FillRect(container,NULL,bg_selected);
    else
        SDL_FillRect(container,NULL,blue_bg);
    //Please resize it before use it
    SDL_Surface *img = IMG_Load(path);
    if(img==NULL){
        SDL_Log("ERRor");
        return ;
    }
    /*image*/
    SDL_Rect title_rect = {10,10,img->h,img->w};
    SDL_BlitSurface(img,NULL,container,&title_rect);
    SDL_Rect container_rect = {x,y,height,width};
    /*fin image*/
    /*nom de pokemon*/
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color white = {255,255,255};
    SDL_Surface *titre = TTF_RenderUTF8_Blended(font,nom,white);
    SDL_Rect nom_rect = {80,10,titre->h,titre->w};
    SDL_BlitSurface(titre,NULL,container,&nom_rect);
    /*fin de pokemon*/
    /*genre*/
    SDL_Surface *genre = TTF_RenderUTF8_Blended(font,gendre,white);
    SDL_Rect genre_rect = {width - genre->w - 20,10,genre->h,genre->w};
    SDL_BlitSurface(genre,NULL,container,&genre_rect);
    /*fin genre*/
    /*hp*/
    SDL_Surface *niv_vie = TTF_RenderUTF8_Blended(font,"HP",white);
    SDL_Rect hp = { 80, 80, niv_vie->h, niv_vie->w };
    SDL_BlitSurface(niv_vie, NULL, container, &hp);
    SDL_Rect bar_vie = {120,85,200,20};
    SDL_Rect bar_vie_sdlon = {120,85,(vie*200)/100,20};
    SDL_FillRect(container,&bar_vie,SDL_MapRGB(container->format,214,248,228));  // 106,238,158
    SDL_FillRect(container,&bar_vie_sdlon,SDL_MapRGB(container->format,106,238,158));
    /*fin hp*/
    /*niveau*/
    char * level_num = malloc(sizeof(char)*MAX_LEN_NAME);
    sprintf(level_num,"Niv. %d",lev);
    SDL_Surface *niveau = TTF_RenderUTF8_Blended(font,level_num,white);
    SDL_Rect niveau_rect = {10,150,niveau->h,niveau->w};
    SDL_BlitSurface(niveau,NULL,container,&niveau_rect);
    /*fin niveau*/
    /*stats*/
    SDL_Surface *stats = TTF_RenderUTF8_Blended(font,"302/302",white);
    SDL_Rect stats_rect = {150,250,stats->h,stats->w};
    SDL_BlitSurface(stats,NULL,container,&stats_rect);
    /*fin stats*/
    SDL_BlitSurface(container,NULL,screen,&container_rect);
    SDL_UpdateWindowSurface(window);
}

void updateSdlons(SDL_Window *window,SDL_Surface *screen,int n,player_t player){
    Uint32 bg = 0x285171;
    SDL_FillRect(screen,NULL,bg);
    /*tittre*/
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color white = {255,255,255};
    SDL_Surface *titre = TTF_RenderUTF8_Blended(font,"Scene de Combat",white);
    SDL_Rect rect = {(WIDTH - titre->w)/2,10,titre->h,titre->w};
    SDL_BlitSurface(titre,NULL,screen,&rect);
    /*fin titre*/
    int y=60,x=30;
    int i;
    for(i=0;i<player.nb_current_sdlon;i++){
        x=(i%2==0)?30:730;
        y=60+(300)*(i/2);
        printSdlonBar(window,screen,500,200,x,y,player.sd[i].nom,"M",(player.sd[i].vie*100)/player.sd[i].vie_max,player.sd[i].level,(n==i),player.sd[i].front_face);
        
    }
    /*printSdlonBar(window,screen,500,200,30,60,"Abdelhak","M",90,10,(n==0));
    printSdlonBar(window,screen,500,200,730,60,"Lilian","M",80,10,(n==1));
    printSdlonBar(window,screen,500,200,30,360,"Mohamed","M",70,10,(n==2));
    printSdlonBar(window,screen,500,200,730,360,"Wandrille","M",30,10,(n==3));*/
    botton(screen,"ANNULER",WIDTH - 60,100,30,700,(n==i));
    SDL_UpdateWindowSurface(window);
}

// max de n  est 4 je crois
int showAllSDlons(SDL_Window *window,SDL_Surface *screen,int n,player_t player){
    
    /*print sdlons*/
    int nb = 0;
    updateSdlons(window,screen,nb,player);
    /*fin sdlons*/
    SDL_UpdateWindowSurface(window);
    int running =1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_QUIT:
                running = 0;
                return;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        nb=(nb-2)%n;
                        break;
                    case SDLK_DOWN:
                        nb=(nb+2)%n;
                        break;
                    case SDLK_LEFT:
                        nb=(nb-1)%n;
                        if(nb<0)
                            nb += n;
                        break;
                    case SDLK_RIGHT:
                        nb=(nb+1)%n;
                        break;
                    case SDLK_RETURN:
                        return nb;
                        break;
                }
                updateSdlons(window,screen,nb,player);
                break;
          }
        }
    }
}

void botton(SDL_Surface *surface,char * titre,int width,int height,int x,int y,int selected){
    SDL_Surface *annuler_rect = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    Uint32 bg = 0x285171;
    Uint32 bg_selected = 0xdaed9c;
    if(selected)
        SDL_FillRect(annuler_rect,NULL,bg_selected);
    else
        SDL_FillRect(annuler_rect,NULL,bg);
    SDL_Color white = {255,255,255};
    SDL_Surface *annuler = TTF_RenderUTF8_Blended(font,titre,white);
    SDL_Rect rect;
    rect.h=annuler->h;
    rect.w=annuler->w;
    rect.y=(height - annuler->h)/2;
    rect.x=(width - annuler->w)/2;
    SDL_BlitSurface(annuler,NULL,annuler_rect,&rect);
    rect.h=height;
    rect.w=width;
    rect.y=y;
    rect.x=x;
    SDL_BlitSurface(annuler_rect,NULL,surface,&rect);
    
}

void drawAllOptions(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int width,int height,int selected,player_t player){
    Uint32 border_color = 0xfbfbf9;
    SDL_FillRect(surface, NULL, border_color);
    SDL_Log("attaque : %s\n",player.sd[0].attaque_1.nom_attaque);
    attaque_graphique(window,screen,180,80,surface,10,10,player.sd[0].attaque_1.nom_attaque,player.sd[0].attaque_1.type_attaque,(0==selected));
    attaque_graphique(window,screen,180,80,surface,210,10,player.sd[0].attaque_2.nom_attaque,player.sd[0].attaque_2.type_attaque,(1==selected));
    attaque_graphique(window,screen,180,80,surface,10,110,player.sd[0].attaque_3.nom_attaque,player.sd[0].attaque_3.type_attaque,(2==selected));
    attaque_graphique(window,screen,180,80,surface,210,110,player.sd[0].attaque_4.nom_attaque,player.sd[0].attaque_4.type_attaque,(3==selected));
    botton(surface,"ANNULER",width-40,40,20,200,(4==selected));
    /*botton d'annuler*/
    
    /*FIN*/
    SDL_Rect pos = { WIDTH-width-20, 560, width, height };
    SDL_BlitSurface(surface, NULL, screen, &pos);
    SDL_UpdateWindowSurface(window);
}

void updateArrowSelector(SDL_Window *window,SDL_Surface * surface,int n){
    
}

void showDescription(SDL_Window *window,SDL_Surface * screen, char * desc){
    SDL_Surface *desc_container = SDL_CreateRGBSurface(0, WIDTH/2, 300, 32, 0, 255, 255, 255);
    SDL_FillRect(desc_container,NULL,0xFFFFFF);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 40);
    SDL_Color white = {0,0,0};
    SDL_Surface *desc_texte = TTF_RenderText_Blended_Wrapped(font,desc,white,desc_container->w);
    SDL_Rect rect_texte = {10,10,desc_texte->h,desc_texte->w};
    SDL_BlitSurface(desc_texte,NULL,desc_container,&rect_texte);
    SDL_Rect rect_container = {0,HEIGHT - desc_container->h,desc_texte->h,desc_texte->w};
    SDL_BlitSurface(desc_container,NULL,screen,&rect_container);
}

/**
 * Fonction permettant d'afficher les items dans le sac
*/
void showItem(SDL_Window *window,SDL_Surface * surface,char * nom, int qnt,int y, player_t player, int index){
    /*Varibles*/
    Uint32 bg = 0xFFFFFF;
    SDL_Color color = {96,96,96};
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    
    /*Conatiner*/
    SDL_Surface *item_container = SDL_CreateRGBSurface(0, (WIDTH/2 - 60), 50, 32, 0, 255, 255, 255);
    SDL_FillRect(item_container,NULL,bg);
    /*texte d'item*/
    SDL_Surface *item_name = TTF_RenderUTF8_Blended(font,nom,color);
    SDL_Rect rect_texte = {30,10,item_name->h,item_name->w};
    SDL_BlitSurface(item_name,NULL,item_container,&rect_texte);
    /*quantite d'item*/
    char * nombre = malloc(sizeof(char )* MAX_LEN_NAME);
    
    sprintf(nombre,"x %d", player.inventaire.list_item[index]);
    SDL_Surface *item_quant = TTF_RenderUTF8_Blended(font,nombre,color);
    SDL_Rect rect_qnt = {(item_container->w - item_quant->w - 20),10,item_quant->h,item_quant->w};
    SDL_BlitSurface(item_quant,NULL,item_container,&rect_qnt);
    SDL_Log("here 3\n");
    /**/
    SDL_Rect rect_container = {30,y,item_container->h,item_container->w};
    SDL_BlitSurface(item_container,NULL,surface,&rect_container);
}


/**
 * Affichage du sac pendant le combat
 * Lit les items dans le tableau générique "items" disponible dans item.h
*/
void showSac(SDL_Window *window,SDL_Surface * screen,char * noms[],char * descs[],int n,player_t player, int (*f)(SDL_Window *window,SDL_Surface * screen,player_t player)){
    Uint32 bg = 0x285171;
    Uint32 items_bg = 0xf8e088;
    item_init();
    SDL_FillRect(screen,NULL,bg);
    SDL_Surface *items_surface = SDL_CreateRGBSurface(0, WIDTH/2, HEIGHT, 32, 0, 219, 233, 172);
    SDL_FillRect(items_surface,NULL,items_bg);
    printf("Path image élément: %s\n", items[0].path);
    SDL_Surface *sac = IMG_Load(items[0].path);
    if(sac)
        SDL_Log("image nice\n");
    SDL_Rect rect = {100,100,sac->h,sac->w};
    SDL_BlitSurface(sac,NULL,screen,&rect);
    int nb=0;
    for(int i=0;i<n;i++){
        SDL_Log("show item %d\n",i);
        showItem(window,items_surface,noms[i],2, (60*i)+40, player, i);
    }
        
    /*description*/
    showDescription(window,screen,descs[nb]);
    /*arraow*/
    SDL_Surface * arrow =  IMG_Load("images/select.png");
    SDL_Rect rect_arrow = {5,40+(60)*(nb)+15,arrow->h,arrow->w};
    SDL_BlitSurface(arrow,NULL,items_surface,&rect_arrow);
    SDL_Rect btn = {30,HEIGHT - 50 - 30,(WIDTH/2 - 60),50};
    SDL_Rect btn_in_screen = {30+WIDTH/2,HEIGHT - 50 - 30,(WIDTH/2 - 60),50};
    SDL_Log("x == %d\n",btn.x);
    //bouton de fermeture du sac
    botton(items_surface,"Fermer le sac",btn.w, btn.h, btn.x, btn.y, 0);
    SDL_Rect items_rect = {WIDTH/2,0,items_surface->h,items_surface->w};
    SDL_BlitSurface(items_surface,NULL,screen,&items_rect);
    SDL_FillRect(items_surface,&rect_arrow,items_bg);
    SDL_UpdateWindowSurface(window);
    
    int running = 1;
    SDL_Point mousePosition;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_QUIT:
                running = 0;
                return ;
                break;
            case SDL_MOUSEBUTTONUP:
                if(SDL_PointInRect(&mousePosition, &btn_in_screen)){
                    f(window,screen,player);
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
                        break;
                }
                SDL_FillRect(items_surface,&rect_arrow,items_bg);
                showDescription(window,screen,descs[nb]);
                
                break;
            case SDL_MOUSEMOTION:
                mousePosition.x = e.motion.x; 
                mousePosition.y = e.motion.y;
                if (SDL_PointInRect(&mousePosition, &btn_in_screen)){
                    botton(items_surface,"Fermer le sac",btn.w, btn.h, btn.x, btn.y, 1);
                }else
                    botton(items_surface,"Fermer le sac",btn.w, btn.h, btn.x, btn.y, 0);
                SDL_BlitSurface(items_surface,NULL,screen,&items_rect);
                SDL_UpdateWindowSurface(window);
          }
                rect_arrow.y = 40+(60)*(nb)+15;
                SDL_BlitSurface(arrow,NULL,items_surface,&rect_arrow);
                
                SDL_BlitSurface(items_surface,NULL,screen,&items_rect);
                SDL_UpdateWindowSurface(window);
        }
    }
}
/*fin sac*/
void handle_option_events(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int width,int height,int n,player_t player, sdlon sd){
    switch(n){
        case 0:
            onAttack(window,screen,surface,width,height,player, sd);
            break;
        case 1: ;
            char * noms[5] = {"Sdlasso","Super-sdlasso","CABB-sdlasso","Relique","Extracteur"};
            char * descs[5] = {"Un objet particulier qui permet de capturer des sdlons.","Un sdlasso renforcer et amélioré qui permet de capturer des sdlons avec un meilleuhr rendement.","Un objet basé sur le fonctionnement des des sdlasso mais perfectionné par des artisants pour fonctionner à tous les coups.","Une relique êxtremement rare n'ayant que peu d'intêret.","Un outil pouvant être utilisé par des chercheur permettant l'extraction d'une relique."};
            SDL_Log("show sac\n");
            showSac(window,screen,noms,descs,5,player,afficherLeCombat);
            return;
            break;
        case 2:;
            int nbRetour = showAllSDlons(window,screen,4,player);
            handle_sdlons_events(window,screen,nbRetour,player,sd);
            break;
        case 3: ;
            player_t temp;
            printMap(window,screen,player);
            break;
        default:
            break;
    }
}

void onAttack(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int width,int height,player_t player, sdlon sd){
    int nb=0;
    drawAllOptions(window,screen,surface,width,height,nb,player);
    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_QUIT:
                running = 0;
                return ;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        nb=(nb-2)%5;
                        break;
                    case SDLK_DOWN:
                        nb=(nb+2)%5;
                        break;
                    case SDLK_LEFT:
                        nb=(nb-1)%5;
                        if(nb<0)
                            nb += 5;
                        break;
                    case SDLK_RIGHT:
                        nb=(nb+1)%5;
                        break;
                    case SDLK_RETURN:
                        return handle_events(window,screen,nb,player,sd);
                        break;
                }
                drawAllOptions(window,screen,surface,width,height,nb,player);
                break;
          }
        }
    }
    return ;
}

void updateOptions(SDL_Window *window,SDL_Surface *screen,SDL_Surface *surface,int n,int width,int height){
    Uint32 border_color = 0xf8f8d8;
    SDL_FillRect(surface, NULL, border_color);
    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color black = {0,0,0};
    SDL_Color red = {255,0,0};

    SDL_Surface *attack = TTF_RenderUTF8_Blended(font,"Attaques",black);
    SDL_Surface *sac = TTF_RenderUTF8_Blended(font,"Sac",black);
    SDL_Surface *sdlon = TTF_RenderUTF8_Blended(font,"SDLon",black);
    SDL_Surface *fuite = TTF_RenderUTF8_Blended(font,"Fuite",black);
    switch (n){
    case 0:
        attack = TTF_RenderUTF8_Blended(font,"Attaques",red);
        break;
    case 1:
        sac = TTF_RenderUTF8_Blended(font,"Sac",red);
        break;
    case 2:
        sdlon = TTF_RenderUTF8_Blended(font,"SDLon",red);
        break;
    case 3:
        fuite = TTF_RenderUTF8_Blended(font,"Fuite",red);
        break;
    
    default:
        break;
    }

    SDL_Rect rect;
    rect.x = 10;
    rect.y=10;
    rect.h=attack->h;
    rect.w=attack->w;
    SDL_BlitSurface(attack,NULL,surface,&rect);
    rect.x = width-sac->w-10;
    rect.y=10;
    rect.h=sac->h;
    rect.w=sac->w;
    SDL_BlitSurface(sac,NULL,surface,&rect);
    rect.x = 10;
    rect.y=height-sdlon->h-10;
    rect.h=sdlon->h;
    rect.w=sdlon->w;
    SDL_BlitSurface(sdlon,NULL,surface,&rect);
    rect.x = width-fuite->w-10;
    rect.y= height-fuite->h - 10;
    rect.h=fuite->h;
    rect.w=fuite->w;
    SDL_BlitSurface(fuite,NULL,surface,&rect);
    SDL_Rect pos = { WIDTH-width-20, 560, width, height };
    SDL_BlitSurface(surface, NULL, screen, &pos);
    SDL_UpdateWindowSurface(window);
}

void printControlles(SDL_Window *window,SDL_Surface * screen,player_t player, sdlon sd){
     
    // Create a surface for the rectangle border
    int width = 400;
    int height = 250;
    SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    // intialisation
    
    //options
    int nb=0;
    updateOptions(window,screen,surface,nb,width,height);
    // Update the screen
    SDL_UpdateWindowSurface(window);
    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent( & e)) {
          switch (e.type) {
            case SDL_QUIT:
                SDL_DestroyWindow(window);
                SDL_Quit();
                running = 0;
                return;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        nb=(nb-2)%4;
                        break;
                    case SDLK_DOWN:
                        nb=(nb+2)%4;
                        break;
                    case SDLK_LEFT:
                        nb=(nb-1)%4;
                        if(nb<0)
                            nb += 4;
                        break;
                    case SDLK_RIGHT:
                        nb=(nb+1)%4;
                        break;
                    case SDLK_RETURN:
                        handle_option_events(window,screen,surface,width,height,nb,player,sd);
                        return ;
                        break;
                }
                updateOptions(window,screen,surface,nb,width,height);
                break;
          }
        }
    }
}

void printPlayerStats(SDL_Window *window,SDL_Surface * screen,char * nom,int x,int y, int niveau,int vie){
    Uint32 border_color = 0xf8f8d8;

    // Create a surface for the rectangle border
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 300, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, border_color);

    TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Color black = {0,0,0};
    SDL_Surface *sdlon_name = TTF_RenderUTF8_Blended(font,nom,black);
    char *lvl = malloc(sizeof(char)*MAX_LEN_NAME);
    sprintf(lvl,"Niv. %d",niveau);
    SDL_Surface *sdlon_level = TTF_RenderUTF8_Blended(font,lvl,black);
    SDL_Surface *niv_vie = TTF_RenderUTF8_Blended(font,"PV",black);
    SDL_Rect nom_rect = { 10, 10, sdlon_name->h, sdlon_name->w };
    SDL_BlitSurface(sdlon_name, NULL, surface, &nom_rect);
    SDL_Rect level = { 300 - sdlon_level->w - 20, 10, sdlon_name->h, sdlon_name->w };
    SDL_BlitSurface(sdlon_level, NULL, surface, &level);
    
    SDL_Rect hp = { 10, 65, niv_vie->h, niv_vie->w };
    SDL_BlitSurface(niv_vie, NULL, surface, &hp);

    SDL_Rect bar_vie = {60,70,200,20};
    SDL_Rect bar_vie_sdlon = {60,70,(vie*200)/100,20};
    SDL_FillRect(surface,&bar_vie,SDL_MapRGB(surface->format,214,248,228));  // 106,238,158
    SDL_FillRect(surface,&bar_vie_sdlon,SDL_MapRGB(surface->format,106,238,158));

    SDL_Rect pos = { x, y, 300, 100 };
    SDL_BlitSurface(surface, NULL, screen, &pos);
    // Update the screen
    SDL_UpdateWindowSurface(window);
}

void printPokemon(SDL_Window *window,SDL_Surface * screen,char *nom_fichier,int x,int y){
    printf("Nom du fichier: %s\n", nom_fichier);
    printf("OK\n");
    SDL_Surface *pokemon = IMG_Load(nom_fichier);
    SDL_Rect dest;
    dest.h = pokemon->h;
    dest.w = pokemon->w;
    dest.x = x;
    dest.y = y;
    SDL_BlitSurface(pokemon,NULL,screen,&dest);
    SDL_UpdateWindowSurface(window);
}
int afficherLeCombat(SDL_Window *window,SDL_Surface * screen,player_t player, sdlon sd){
    //sdlon sd = generate_sdlon(0,1,15);
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    /*Afficher la map*/
    printLayer(window,screen,combat_sol,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,combat_ciel,"images/pokemon_style.png",1,16,16);
    printLayer(window,screen,combat_arbre,"images/pokemon_style.png",1,16,16);

    printPokemon(window,screen,sd.front_face,WIDTH-200,200);
    printf("In use: %d\n", player.sd_in_use);
    printf("Path sdlon in use: %s\n", player.sd[player.sd_in_use].back_face);
    printf("Path sdlon 0: %s\n", player.sd[0].back_face);
    printPokemon(window,screen,player.sd[player.sd_in_use].back_face,0,HEIGHT-200);//player indice in use bug. jpense ca viens du pointeur du sdlon courrant
    SDL_Log("vie courante %d\tvie max %d\n",player.sd[player.sd_in_use].vie,player.sd[0].vie_max);
    SDL_Log("niveau %d\n",player.sd[0].level);
    printPlayerStats(window,screen,player.sd[0].nom,20,30,player.sd[0].level,(player.sd[0].vie*100)/player.sd[0].vie_max);
    printPlayerStats(window,screen,sd.nom,WIDTH-320,450,sd.level,100);

    printControlles(window,screen,player,sd);
    return 0;
    // int running = 1;
    // while (running) {
    //     SDL_Event e;
    //     while (SDL_PollEvent( & e)) {
    //       switch (e.type) {
    //         case SDL_QUIT:
    //             SDL_DestroyWindow(window);
    //             SDL_Quit();
    //             running = 0;
    //             return 0;
    //             break;
    //       }
    //     }
    // }
}