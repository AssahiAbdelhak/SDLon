/**
Initialisation structures
*/
typedef struct struct_attaque {
  char *nom_attaque;
  int type_attaque;
  int mode_attaque;
  int degat;
} attaque;

typedef struct struct_sdlon {
  int type;
  char *nom;
  int vie;
  attaque *attaque_1;
  attaque *attaque_2;
  attaque *attaque_3;
  attaque *attaque_4;
} sdlon;

/**
déclaration des prototypes des fonctions
*/
extern attaque *attaque_init();
extern sdlon *sdlon_init(attaque *attaques);
extern int display_sdlon(sdlon *s);
extern int sdlon_quit(sdlon *sdlons, attaque *attaques);
extern int sdlon_is_init(sdlon *sd);
extern int attaque_is_init(sdlon *at);