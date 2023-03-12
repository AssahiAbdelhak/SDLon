#ifndef NB_ITEMS

#define NB_ITEMS 5
#define MAX_LEN_NAME 80
#define MAX_LEN_DESCR 250
#define MAX_LEN_PATH 250
#define MAX_ITEM_PER_SLOT 100

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

typedef struct inventory_s{
    int list_item[NB_ITEMS];
    int max_item_per_slot;
    char * path_to_save;
}inventory;

int item_init();
int display_all_items();
int item_quit();

#endif