#include <iostream>
#include <cassert>

using namespace std;

int compute(int arg1, int arg2, unsigned char funcmask);
int add(int x, int y);
int subtract(int x, int y);
int multiply(int x, int y);

int (*compute_arr[])(int,int) = {add, subtract, multiply};

int main() {
    unsigned char mask = 1;
    cout << compute(1,2,mask) << endl;  //mask = 0001
    mask <<= 1;
    cout << compute(2,1,mask) << endl;  //mask = 0010
    mask <<= 1;
    cout << compute(2,1,mask) << endl;  //mask = 0100

    mask = 1;
    assert(compute(2,2,(mask << 2)) == 4);
    assert(compute(2,3,(mask << 0)) == 5);
    assert(compute(2,2,(mask << 1)) == 0);
    assert(compute(6,3,(mask << 1)) == 3);

    return 0;
}

int compute(int arg1, int arg2, unsigned char funcmask) {
    return (*compute_arr[funcmask >> 1])(arg1, arg2);   //need to shift 1 right to compensate for use of the mask
}

int add(int x, int y) {
    return x + y;
}

int subtract(int x, int y) {
    return x - y;
}

int multiply(int x, int y) {
    return x * y;
}