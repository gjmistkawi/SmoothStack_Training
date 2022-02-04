all: matrix-mult

matrix-mult:
	g++ -c matrix-mult.cpp -o matrix-mult.o -fopenmp
	g++ matrix-mult.o -o matrix-mult -fopenmp -lpthread

clean:
	rm matrix-mult *.o
