CC = clang++
CXXFLAGs = -std=c++17 -Wall

all: mainapp tests

mainapp: bankcli.o account.o user.o bank.o
	$(CC) $(CXXFLAGS) -o bankcli bankcli.o account.o user.o bank.o

tests: tests.o account.o user.o bank.o
	$(CC) $(CXXFLAGS) -o tests tests.o account.o user.o bank.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm bankcli tests *.o