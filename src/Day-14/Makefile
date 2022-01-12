CC = clang++
CXXFLAGs = -std=c++17

all: copy main

copy: copy-assign.o
	$(CC) $(CXXFLAGS) -o copy copy-assign.o

main: shape2d.o vertex.o main.o
	$(CC) $(CXXFLAGS) -o main shape2d.o vertex.o main.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm copy main *.o