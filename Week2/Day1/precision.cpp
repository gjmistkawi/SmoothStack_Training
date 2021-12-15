#include <iostream>
#include <cassert>
#include <limits.h>

using namespace std;

void getInfo(int& sign, int& mantissa, int& exp, float num) {
    unsigned int* ptr = (unsigned int*)&num;

    sign = *ptr >> 31;
    exp = *ptr & 0x7f800000;
    exp >>= 23;
    mantissa = *ptr & 0x007fffff;
}

int main() {
    assert(CHAR_BIT * sizeof(float) == 32);

    float num;
    int S, J, N;
    cout << "Enter decimal: ";
    cin >> num;

    getInfo(S, J, N, num);


    cout << "J = " << J << ", N = " << N << endl;
    cout.precision(20);
    cout << num << endl; 

    return 0;
}