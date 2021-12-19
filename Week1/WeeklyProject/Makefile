CC = clang++
CXXFLAGs = -std=c++17 -Wall
SSLFLAGS = -lcrypto -lssl

all: mainapp tests

mainapp: bankcli.o account.o user.o bank.o transaction.o
	$(CC) $(CXXFLAGS) -o bankcli bankcli.o account.o user.o bank.o transaction.o $(SSLFLAGS)

tests: tests.o account.o user.o bank.o transaction.o
	$(CC) $(CXXFLAGS) -o tests tests.o account.o user.o bank.o transaction.o $(SSLFLAGS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm bankcli tests *.o