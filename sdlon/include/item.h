#ifndef NB_ITEMS
#define NB_ITEMS 5

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

int item_init();
int display_all_items();
int item_quit();

#endif