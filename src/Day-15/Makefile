CC = clang++
CXXFLAGs = -std=c++17

all: main

main: main.o
	$(CC) $(CXXFLAGS) -o main main.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main *.o