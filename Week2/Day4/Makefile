CC = clang++
CXXFLAGs = -std=c++17 -Wall

all: merge-sort grades

meothd: grades.o
	$(CC) $(CXXFLAGS) -o grades grades.o

meothd: merge-sort.o
	$(CC) $(CXXFLAGS) -o merge-sort merge-sort.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm grades merge-sort *.o