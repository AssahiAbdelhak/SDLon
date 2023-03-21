/*#include "player.h"
#include "sdlon_init.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Primitives_Box.h"

void precedentBox(){
    boiteASdlon = boiteASdlon->precedent;
}

void enTeteBox(){
    while(boiteASdlon->precedent != NULL){
        precedentBox();
    }
}

void suivantBox(){
    boiteASdlon = boiteASdlon->next;
}

void append(box** head_ref, sdlon new_data) {
    box* new_sdlon = malloc(sizeof(box));
    box *last = *head_ref;
    new_sdlon->current = new_data;
    new_sdlon->next = NULL;
    if (*head_ref == NULL) {
       *head_ref = new_sdlon;
       return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_sdlon;
    last->next->precedent = last;
    return;
}

void displayBox(box* head) {
    box* aux = head;

    while (aux != NULL) {
        afficheSDLon((*aux).current);
        aux = aux->next;
    }
    printf("\n");
}*/