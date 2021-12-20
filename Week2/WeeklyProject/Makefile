CC = clang++
CXXFLAGs = -std=c++17 -Wall
SSLFLAGS = -lcrypto -lssl

all: mainapp tests

mainapp: bankcli.o account.o user.o bank.o transaction.o protoreadwrite.o bank.pb.o
	$(CC) $(CXXFLAGS) -o bankcli bankcli.o account.o user.o bank.o transaction.o protoreadwrite.o bank.pb.o $(SSLFLAGS) `pkg-config --cflags --libs protobuf`

tests: tests.o account.o user.o bank.o transaction.o
	$(CC) $(CXXFLAGS) -o tests tests.o account.o user.o bank.o transaction.o protoreadwrite.o bank.pb.o $(SSLFLAGS) `pkg-config --cflags --libs protobuf`

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^

clean:
	rm bankcli tests *.o