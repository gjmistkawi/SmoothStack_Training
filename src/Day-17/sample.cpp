#include <iostream>

using namespace std;

template <typename T, typename Q>
struct A {
    T amt;
    A(T amt) : amt(amt) {}
    template <typename R>
    A<R, Q> convert() {
        A<R, Q> a(amt);
        return a;    
    }
    template <typename Adder>
    A operator+(const Adder a) {
        A<T, Q> t(amt + a);
        return t;
    }
};

int main(void) {
    A<int, float> a(3);
    cout << a.amt << endl;

    A<float, float> a1 = a.convert<float>();
    cout << a1.amt << endl;

    A<int, float> a2 = a + 4;
    cout << a2.amt << endl;

    
}