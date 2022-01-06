CC = clang++
CXXFLAGs = -std=c++17

all: main

main: sentence.o main.o
	$(CC) $(CXXFLAGS) -o main sentence.o main.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main *.o