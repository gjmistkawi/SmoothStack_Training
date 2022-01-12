#include <cassert>
#include <iostream>

using namespace std;

bool isInt(float x);
float* compare(float* x, float* y);

int main(void) {
    float* x = new float(6.0);
    float* y = new float(5.0);

    float* temp = compare(x,y);

    assert(temp == x);

    float* z = new float(5.1);
    compare(z,y);

    delete x;
    delete y;

    return 0;
}

bool isInt(float x) {
    int temp = x;
    if((x-temp) == 0.)
        return true;
    else 
        throw invalid_argument("The float is not compatible to int.");
}

float* compare(float* x, float* y) {
    try {
        isInt(*x);
        isInt(*y);

        if(*x == *y)
            return 0;
        else if(*x > *y)
            return x;
        else
            return y;
    }

    catch(string msg) {
        cout << msg << endl;
    }
}