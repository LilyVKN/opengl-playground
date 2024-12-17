DIR_INCLUDE := ./include
DIR_LIBRARY := ./lib

CC		  	:= g++
CC_FLAGS	:= -g -Wall -I ${DIR_INCLUDE} -L ${DIR_LIBRARY}

all: main.o
	${CC} ${CC_FLAGS} -o main main.o -lX11 -lGL -lGLU -lglfw

main.o:
	${CC} ${CC_FLAGS} -c -o main.o ./src/main.cpp

clobber:
	rm *.o
	rm main