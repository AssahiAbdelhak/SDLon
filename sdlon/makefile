CC=gcc
FLAGS=-Wall -g

SDL_DIR=${HOME}/Document/projet/sdlon
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2
INCS=-I${SDL_INC_DIR}
PROG=sdlon

all: sdl_text

sdl_text: sdl_test.c
	${CC} -o ${PROG} sdl_test.c ${LIBS} ${INCS} ${FLAGS}

clean:
	rm -f ${PROG}
	rm -f *.o
