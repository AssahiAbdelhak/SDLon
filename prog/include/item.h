#ifndef NB_ITEMS

/**
 * Déclaration des macros
*/
#define NB_ITEMS 5
#define MAX_LEN_NAME 80
#define MAX_LEN_DESCR 250
#define MAX_LEN_PATH 250
#define MAX_ITEM_PER_SLOT 100

/**
 * Définiton des numéros d'items
*/
#define SDLASSO 0
#define SUPER_SDLASSO 1
#define CABB_SDLASSO 2
#define RELIQUE 3
#define EXTRACTEUR 4

/**
 * structure pour la gestion d'item
 * nom d'un item, description, et toutes ses spec
*/
typedef struct item_s{
    char * name;
    char * description;
    int type;
    int usage;
    int opt_degat;
    int opt_tag;
}item_t;

/**
 * structure de l'inventaire
 * facultatif mais facilite sa mise en place
*/
typedef struct inventory_s{
    int list_item[NB_ITEMS];
    int max_item_per_slot;
    char * path_to_save;
}inventory;

/**
 * déclaration des fonctions accessible
*/
extern int item_init();
extern int display_all_items();
extern int item_quit();

extern item_t items[NB_ITEMS];

#endif