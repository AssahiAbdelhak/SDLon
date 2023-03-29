/**
* @file test_header.c
* Fichier de tests des headers 
* @author Wandrille Ballereau
* @author Abdelhak Assahi
* @author Lilian Colla
* @author Mohamed Besbes
* @date 2023
* @version 1.0 Alpha
*
*/
#include "test_header.h"
#include <stdio.h>


/**
 * @brief affiche l'etat du test
 * dans le cas ou le resultat du test = 1
*/
void posi_test_print(int test, int verbose){

  if(verbose){
    test? printf("-->OK\n\n"):printf("-->KO\n\n");
  }
  
  return;
}

/**
 * @brief affiche l'etat du test
 * dans le cas ou le resultat du test = 0
*/
void nega_test_print(int test, int verbose){

  if(verbose){
    !test? printf("-->OK\n\n"):printf("-->KO\n\n");
  }
  
  return;
}

/**
 * @brief Affiche le test actuelle
*/
void affiche_test(char * str, int verbose){
  if(verbose){
    printf("---Test %s:\n", str);
  }
  
  return;
}

/**
 * @brief Affiche la fiabilité d'une donnée
 * ratio entre le nombre d'une donnée
 * et le nombre de génération au cours du test
*/
void affiche_fiability(char * str, int nb_data, float nb_gen, int verbose){
  if(verbose){
    //affichage de la fiabilité des génération
    printf("Fiabilité de %s: %0.3f\n\n", str, 1-(nb_data/nb_gen));
  }
}
