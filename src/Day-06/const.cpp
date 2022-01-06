#include <iostream>

using namespace std;

struct my_struct {
    void myfunc(float f) {
        cout << "regular" << endl;
    }

    void myfunc(float f) const {
        cout << "const" << endl;
    }
};


int main() {
    float f = 1.333;
    my_struct m = my_struct();
    
    m.myfunc(1.33);
    const_cast<const my_struct&>(m).myfunc(1.33);

    return 0;
}