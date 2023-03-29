#include "stdio.h"
#include "stdlib.h"
#include "time.h"
/**
 * @brief retourne un entier au hazard entre min et max
*/
int rng (int min, int max) {
    srand(time(NULL)); // initialisation de la génération aléatoire
    return rand() % (max - min + 1) + min; // renvoie un entier aléatoire entre min et max (inclus)
}
/**
 * @brief retourne un pointeur sur une replique de pnj
*/
char * pnjSpeak(int choix){
    switch (choix){
        case 0 : 
            char str1[] = "Bonjour, bienvenue au centre SDLon. Nous pouvons soigner vos SDLon pour les remettre en forme et les soigner de toutes les blessures qu'ils ont subies lors de vos combats. Veuillez nous confier vos SDLon, nous en prendrons grand soin.";
            return str1;
            break;
        case 1 :
            char str1[] = "Pourquoi les plongeurs plongent-ils toujours en arrière et jamais en avant ?\nParce que sinon ils tombent dans le bateau !";
            return str1;
            break;
        case 2 :
            char str1[] = "Pourquoi les oiseaux ne jouent-ils jamais au football ?\nParce qu'ils ont peur des cages !";
            return str1;
            break;
        case 3 :
            char str1[] = "01001010 00100111 01100001 01101001 00100000 01100101 01101110 01110110 01101001 01100101 00100000 01100100 01100101 00100000 01100011 01100001 01101110 01101110 01100101 01110010";
            return str1;
            break;
        case 4 : 
            char str1[] = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
            return str1;
            break;
        case 5 :
            char str1[] = "Quoi !?  \nFeur ...";
            return str1;
            break;
        case 6 :
            char str1[] = "Ok quoicoubeh!";
            return str1;
            break;
        case 7 :
            char str1[] = "Pourquoi tant de poissons vivent-ils dans l'eau salée?\nParce que l'eau poivrée les ferait éternuer!";
            return str1;
            break;
        case 8 :
            char str1[] = "6A 27 61 69 20 65 75 20 75 6E 65 20 73 61 6C 65 20 6E 6F 74 65 20 65 6E 20 70 72 6F 62 61 2E 20 43 6F 6D 6D 65 20 74 6F 75 74 20 6C 65 20 6D 6F 6E 64 65 20 65 6E 66 61 69 74 21";
            return str1;
            break;
        case 9 :
            char str1[] = "Qu'est-ce qui est jaune et qui attend ? Jonathan !!!";
            return str1;
            break;
        case 10 :
            char str1[] = ".--- . / ... ..- .. ... / .- -- --- ..- .-. . ..- -..- / -- .- .. ... / .--- .----. .- .-. .-. .. ...- . / .--. .- ... / .- / .- ...- --- ..- . .-. / -- . ... / ... . -. - .. -- . -. - ...";
            return str1;
            break;
    }

}