CC = clang++
CXXFLAGs = -std=c++17

all: main

main: mystring.o main.o
	$(CC) $(CXXFLAGS) -o main mystring.o main.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main *.o