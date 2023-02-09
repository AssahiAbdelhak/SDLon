//macros
#define NB_SDLON 12
#define NB_ATTAQUE 10

/**
Initialisation structures
*/
typedef struct struct_attaque {
  char nom_attaque[50];
  int type_attaque;
  int mode_attaque;
  int degat;
} attaque;

typedef struct struct_sdlon {
  int type;
  char nom[50];
  int vie;
  attaque attaque_1;
  attaque attaque_2;
  attaque attaque_3;
  attaque attaque_4;
  int evolution;
} sdlon;

/**
déclaration des prototypes des fonctions
*/
extern int sdlon_init();

//extern const int NB_SDLON;
extern sdlon sdlon_s[NB_SDLON];