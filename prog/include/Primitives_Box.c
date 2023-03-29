/**
* @file Primitives_Box.c
* Fichier de la box a sdlon 
* @author Wandrille Ballereau
* @author Abdelhak Assahi
* @author Lilian Colla
* @author Mohamed Besbes
* @date 2023
* @version 1.0 Alpha
*
*/

#include "player.h"
#include "sdlon_init.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Primitives_Box.h"
/**
 * @brief retourne le sdlon recedent dans la box
*/
void precedentBox(){
    boiteASdlon = boiteASdlon->precedent;
}
/**
 * @brief retourne en tete de la box a sdlon
*/
void enTeteBox(){
    while(boiteASdlon->precedent != NULL){
        precedentBox();
    }
}
/**
 * @brief passe au sdlon suivant
*/
void suivantBox(){
    boiteASdlon = boiteASdlon->next;
}
/**
 * @brief rajoute un sdlon a la box
*/
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
/**
 * @brief affiche les sdlons de la box "debogage"
*/
void displayBox(box* head) {
    box* aux = head;

    while (aux != NULL) {
        afficheSDLon((*aux).current);
        aux = aux->next;
    }
    printf("\n");
}