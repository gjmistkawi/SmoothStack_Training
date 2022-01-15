CC = clang++
CXXFLAGs = -std=c++17

all: main sample

main: main.o currency.o account.o
	$(CC) $(CXXFLAGS) -o main main.o currency.o account.o

sample: sample.o
	$(CC) $(CXXFLAGS) -o sample sample.o

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm main sample *.o