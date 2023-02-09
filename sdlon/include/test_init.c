#include "sdlon_init.h"
#include <stdio.h>

int main() {

  sdlon_init();
  
  int i;
  for(i=0;i<NB_SDLON;i++){
    printf("nom: %s, type: %d, vie: %d, evolution: %s, attque 1: %s\n", sdlon_s[i].nom, sdlon_s[i].type, sdlon_s[i].vie, sdlon_s[i].evolution, sdlon_s[i].attaque_1.nom_attaque);
  }
  return 0;
}