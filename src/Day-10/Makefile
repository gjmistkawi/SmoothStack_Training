CC = clang++
CXXFLAGs = -std=c++17

all: main

main: person.o main.o
	$(CC) $(CXXFLAGS) -o main person.o main.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main *.o