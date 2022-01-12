#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

class A {
    A(const A&) = delete;
};

class B {
    string str[2];
};

class C {
    int n;
public:
    C(const C&) = default;
};

class D {
    vector<int> n;
public:
    D(const D&) = default;
};

class E {
public:
    E(const E&) = default;
};

int main() {
    assert(!is_copy_constructible<A>::value);
    assert(is_copy_constructible<B>::value);
    assert(is_copy_constructible<C>::value);
    assert(is_nothrow_copy_constructible<C>::value);
    assert(is_trivially_copy_constructible<C>::value);
    assert(is_copy_constructible<D>::value);
    assert(!is_nothrow_copy_constructible<D>::value);
    assert(!is_trivially_copy_constructible<D>::value);
    assert(is_copy_constructible<E>::value);
    assert(is_nothrow_copy_constructible<E>::value);
    assert(is_trivially_copy_constructible<E>::value);
    return 0;
}