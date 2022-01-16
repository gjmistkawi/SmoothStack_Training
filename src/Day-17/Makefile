CC = clang++
CXXFLAGs = -std=c++17

all: main

main: main.o currency.o account.o convert.o
	$(CC) $(CXXFLAGS) -o main main.o currency.o account.o convert.o

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main *.o