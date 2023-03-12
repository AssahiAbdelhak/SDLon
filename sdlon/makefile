CC=gcc
FLAGS=-Wall -g
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=prog
all: sdl_text
sdl_text: sdlon.c
	${CC} -o ${PROG} sdlon.c ${LIBS} ${INCS} ${FLAGS}

windows: wind
wind: sdlon.c
	${CC} -o ${PROG} sdlon.c map.c constants.c -IC:\Users\bdalh\Desktop\developpement\x86_64-w64-mingw32\include -LC:\Users\bdalh\Desktop\developpement\x86_64-w64-mingw32\lib  -w -mconsole -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
clean:
	rm -f ${PROG}
	rm -f *.o
