CC = clang++
CXXFLAGS = -std=c++17
GRAPH = -I/usr/include/python2.7/Python.h

all: main

main: main.o body.o
	$(CC) $(CXXFLAGS) $(GRAPH) -o main main.o body.o -pthread -lpython2.7

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main *.o