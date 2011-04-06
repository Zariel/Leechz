CC=g++
CFLAGS=-std=c++0x -g
LIBS=-lpthread
OBJECTS=usenet.o

all: leechz

leechz: threadp.o usenet.o leechz.o con_pool.o
	$(CC) $(CFLAGS) $(LIBS) threadp.o usenet.o con_pool.o leechz.o -o leechz

usenet.o: usenet.cpp usenet.h threadp.o
	$(CC) $(CFLAGS) -c usenet.cpp -o usenet.o

con_pool.o: con_pool.cpp con_pool.h threadp.o
	$(CC) $(CFLAGS) -c con_pool.cpp -o con_pool.o

leechz.o: leechz.cpp leechz.h
	$(CC) $(CFLAGS) -c leechz.cpp -o leechz.o

threadp.o: threadp.cpp threadp.h
	$(CC) $(CFLAGS) -c threadp.cpp -o threadp.o
