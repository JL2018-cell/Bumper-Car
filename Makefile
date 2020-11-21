# Define required macros here
SHELL = /bin/sh

OBJS =  bumper.o screen.o car.o
CFLAGS = -Wall -g -O0  
CC = g++
INCLUDE =  -I./
LIBS = -lm

bumper:${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
	rm -f *.o core *.core bumper

.cpp.o:
	${CC} ${CFLAGS} ${INCLUDE} -c $*.cpp

