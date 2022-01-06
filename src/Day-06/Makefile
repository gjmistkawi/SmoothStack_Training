CC = clang++
CXXFLAGs = -std=c++17 -Wall

all: const power precision

const: const.o
	$(CC) $(CXXFLAGS) -o const const.o

power: power.o
	$(CC) $(CXXFLAGS) -o power power.o	

precision: precision.o
	$(CC) $(CXXFLAGS) -o precision precision.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm const power precision *.o