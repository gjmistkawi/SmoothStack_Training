CC = clang++
CXXFLAGs = -std=c++17 -Wall

all: longmult calander

longmult: longmult.o
	$(CC) $(CXXFLAGS) -o longmult longmult.o

calander: calander.o
	$(CC) $(CXXFLAGS) -o calander calander.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm longmult calander *.o