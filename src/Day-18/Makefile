CC = clang++
CXXFLAGs = -std=c++17

all: main

main: main.o myvector.o
	$(CC) $(CXXFLAGS) -o main main.o myvector.o

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main *.o