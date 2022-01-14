#include <cassert>
#include <iostream>

using namespace std;

string err = "The float is not compatible to int.";


bool isInt(float x);
bool compare(float x, float y);

int main(void) {
    float x = 6.0;
    float y = 5.0;
    float z = 5.1;

    assert(compare(x,y));
    assert(!compare(z,y));
    assert(compare(y,-1));


    return 0;
}

bool isInt(float x) {
    int temp = x;
    if((x-temp) == 0.)
        return true;
    else
        throw invalid_argument(err);
}

bool compare(float x, float y) {
    try {
        isInt(x);
        isInt(y);
    }

    catch(invalid_argument& e) {
        assert(e.what() == err);
        return false;
    }

    if(x > y)
        return true;
    else
        return false;
}