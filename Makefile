CC=g++
CFLAGS=-std=c++0x -g
LIBS=-lpthread
OBJECTS=usenet.o

all: leechz

leechz: threadp.o usenet.o leechz.o
	$(CC) $(CFLAGS) $(LIBS) threadp.o usenet.o leechz.o -o leechz

usenet.o: usenet.cpp usenet.h
	$(CC) $(CFLAGS) -c usenet.cpp -o usenet.o

leechz.o: leechz.cpp leechz.h
	$(CC) $(CFLAGS) -c leechz.cpp -o leechz.o

threadp.o: threadp.cpp threadp.h
	$(CC) $(CFLAGS) -c threadp.cpp -o threadp.o
