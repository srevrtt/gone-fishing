# only windows support here

CC= g++
ARGS= -std=c++17 -g -O3 -m64 -lstdc++
INCDIR= -Idependencies
LIBDIR= -Ldependencies/sdl2/lib
BINDIR= bin/gone_fishing
LIBS= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

all: build clean run

build:
	${CC} -c ./src/*.cpp ${ARGS} ${INCDIR}
	${CC} -mwindows -static-libgcc -static-libstdc++ *.o -o ${BINDIR} ${LIBDIR} ${LIBS}

clean:
	del *.o

run:
	./${BINDIR}.exe

.PHONY: all build clean run