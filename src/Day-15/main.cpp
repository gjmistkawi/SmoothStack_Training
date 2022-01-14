#include <cassert>
#include <iostream>

using namespace std;


class MyFloat {
private:
    string err = "The float is not compatible to int.";
    float num;

    bool isInt(float x) {
        int temp = x;
        if((x-temp) == 0.)
            return true;
        else
            throw invalid_argument(err);
    }

public:
    MyFloat(float f) {
        isInt(f);
        num = f;
    }
    

    bool operator >(const MyFloat &f) {
        return (num > f.num);
    }
};

bool compare(float x, float y) {
    return MyFloat(x) > MyFloat(y);
}

int main(void) {
    float x = 6.0;
    float y = 5.0;
    float z = 5.1;

    try {
        assert(compare(x,y));
        assert(!compare(z,y));
        assert(compare(y,-1));
    }

    catch(invalid_argument& e) {
        cout << e.what() << endl;
    }

    return 0;
}
