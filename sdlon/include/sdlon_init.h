//macros
#define NB_SDLON 15
#define NB_ATTAQUE 10

#define EAU 0
#define TERRE 1
#define AIR 2
#define FEU 3

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
  int vie_max;
  int vie;
  attaque attaque_1;
  attaque attaque_2;
  attaque attaque_3;
  attaque attaque_4;
  int evolution;
  int level;
  int evol_sys;
  int xp;
} sdlon;

/**
déclaration des prototypes des fonctions
*/
extern int sdlon_init();

//extern const int NB_SDLON;
extern sdlon sdlon_s[NB_SDLON];