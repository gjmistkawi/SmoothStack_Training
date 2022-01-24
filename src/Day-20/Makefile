CC = clang++
CXXFLAGS = -std=c++17
GRAPH = -I/usr/include/python2.7/Python.h

all: main

main: main.o body.o
	$(CC) $(CXXFLAGS) $(GRAPH) -o main main.o body.o -lpython2.7

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp 

body.o: body.cpp
	$(CC) $(CXXFLAGS) -c body.cpp 

clean:
	rm main *.o