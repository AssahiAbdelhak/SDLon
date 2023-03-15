#include "Primitives_Box.h"
#include "sdlon_generate.h"
#include "combat.h"
#include "test_header.h"
#include "player.h"
#include "item.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void){
    int i;
    sdlon sd;
    
    //test de la creation de la box
    create_box();

    for (i = 0; i < 3; i++){
        sd = generate_sdlon(0,1,15);
        append(&boiteASdlon, sd);
        printf("a");
    }
    displayBox(boiteASdlon);
    return 0;
}