CC = clang++
CXXFLAGS = -std=c++17

all: anyof noneof

anyof: anyof.o
	$(CC) $(CXXFLAGS) -o anyof anyof.o -pthread

noneof: noneof.o
	$(CC) $(CXXFLAGS) -o noneof noneof.o -pthread

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm anyof noneof *.o