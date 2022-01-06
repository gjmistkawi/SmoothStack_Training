#include <iostream>
#include <math.h>
#include <cassert>

using namespace std;


long nthFibonacci(int n) {
    float phi = (1 + pow(5, 0.5)) / 2;
    float psi = -1 / phi;

    return (pow(phi, n) - pow(psi, n)) / (phi - psi);
}

int largestFibonacci(int bBit) {
    float phi = (1 + pow(5, 0.5)) / 2;
    float psi = -1 / phi;

    // F(n) < 2^b
    int n = floor((bBit*(log(2)/log(phi)) + 0.5*(log(5)/log(phi))));

    return n;
}

void print(int bBit, int n) {
    cout << "b-bit: " << bBit << ", index: " << n << endl;
    cout << "fibonacci number: " << nthFibonacci(n) << endl;
}


int main() {
    int bBit = (sizeof(int)*8) - 1;
    int n = largestFibonacci(bBit);
    assert(n == 46); //bruteforced for answer to test
    print(bBit, n);

    bBit = (sizeof(long)*8) - 1;
    n = largestFibonacci(bBit);
    assert(n == 92); //bruteforced for answer to test
    print(bBit, n);

    return 0;
}