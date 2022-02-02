CC = clang++
CXXFLAGS = -std=c++17

all: main

main: main.o safe-queue.o
	$(CC) $(CXXFLAGS) -o main main.o safe-queue.o -pthread

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main *.o