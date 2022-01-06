CC = clang++
CXXFLAGs = -std=c++17 -Wall

all: overflow fibonacci

overflow: overflow.o
	$(CC) $(CXXFLAGS) -o overflow overflow.o

fibonacci: fibonacci.o
	$(CC) $(CXXFLAGS) -o fibonacci fibonacci.o	

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm overflow fibonacci *.o