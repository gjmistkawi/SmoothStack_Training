CC = clang++
CXXFLAGS = -std=c++17

all: async parallel

async: async.o
	$(CC) $(CXXFLAGS) -o async async.o -pthread

parallel: parallel.o
	$(CC) $(CXXFLAGS) -o parallel parallel.o -pthread

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm async parallel *.o