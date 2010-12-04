CC=g++
CFLAGS=
LIBS=-lpthread
OBJECTS=usenet.o 

all: leechz

leechz: usenet.o leechz.o
	$(CC) $(CFLAGS) $(LIBS) usenet.o leechz.o -o leechz

usenet.o: usenet.cpp
	$(CC) $(CFLAGS) -c usenet.cpp -o usenet.o

leechz.o: leechz.cpp
	$(CC) $(CFLAGS) -c leechz.cpp -o leechz.o
