#ifndef NB_SDLON
//macros
#define NB_SDLON 30
#define NB_ATTAQUE 10

#define EAU 0
#define TERRE 1
#define AIR 2
#define FEU 3
#define HEAL 0
#define ATT 1

/**
Initialisation structures
*/
typedef struct struct_attaque {
  char nom_attaque[50];
  int type_attaque; //eau : 0, terre : 1, air : 2, feu : 3 
  int mode_attaque; // Heal : 0 , Degat : 1
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
  int evolution; //indice de l'evolution dans le tableau, 0 si pas d'evolution
  int level;
  int evol_sys; //nombre avec premier chiffre, evolution courrante et 2e chiffre evolution total  
  int xp;
  char front_face[200];
  char back_face[200];
} sdlon;

/**
déclaration des prototypes des fonctions
*/
extern int sdlon_init();
extern int get_sdlon_index(char * name);
extern int sdloncmp(sdlon sd_src, sdlon sd_origin);
extern void afficheSDLon(sdlon s);

extern sdlon sdlon_s[NB_SDLON];
#endif