#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    
    SDL_version nb;
    SDL_VERSION(&nb);

    printf("%d.%d.%d", nb.major, nb.minor, nb.patch);

    return 0;
    //gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
}