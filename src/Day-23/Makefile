CC = clang++
CXXFLAGS = -std=c++17

all: hailstone country

hailstone: hailstone.o
	$(CC) $(CXXFLAGS) -o hailstone hailstone.o -pthread

country: country.o
	$(CC) $(CXXFLAGS) -o country country.o -pthread

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm country hailstone *.o