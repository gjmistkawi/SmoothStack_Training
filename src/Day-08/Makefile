CC = clang++
CXXFLAGs = -std=c++17 -Wall

all: method

meothd: method.o
	$(CC) $(CXXFLAGS) -o method method.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm method *.o