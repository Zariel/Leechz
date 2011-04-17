CC=g++
CFLAGS=-std=c++0x -g
LIBS=-lpthread

all: leechz

leechz: threadp.o con_pool.o usenet.o leechz.o
	$(CC) $(CFLAGS) $(LIBS) threadp.o usenet.o con_pool.o connection.o leechz.o -o leechz

usenet.o: usenet.cpp usenet.h threadp.o connection.o
	$(CC) $(CFLAGS) -c usenet.cpp -o usenet.o

connection.o: connection.cpp connection.h threadp.o
	$(CC) $(CFLAGS) -c connection.cpp -o connection.o

con_pool.o: con_pool.cpp con_pool.h threadp.o usenet.o
	$(CC) $(CFLAGS) -c con_pool.cpp -o con_pool.o

leechz.o: leechz.cpp leechz.h
	$(CC) $(CFLAGS) -c leechz.cpp -o leechz.o

threadp.o: threadp.cpp threadp.h
	$(CC) $(CFLAGS) -c threadp.cpp -o threadp.o

