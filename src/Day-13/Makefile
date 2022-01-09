CC = clang++
CXXFLAGs = -std=c++17

all: main

main: shape2d.o vertex.o main.o
	$(CC) $(CXXFLAGS) -o main shape2d.o vertex.o main.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main *.o