CC = clang++
CXXFLAGs = -std=c++17

all: main

main: main.o number.o
	$(CC) $(CXXFLAGS) -o main main.o number.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main *.o