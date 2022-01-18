#include <cassert>
#include <iostream>
#include "myvector.cpp"

using namespace std;

int main(void) {
    myvector<int> m;
    m.push_back(3);
    assert(m[0] == 3);
    assert(m.at(0) == 3);

    m.push_back(1);
    assert(m[0] == 3);
    assert(m[1] == 1);
    assert(m.size() == 2);
    assert(m.capacity() == 2);

    myvector<int> m1((const myvector<int>&) m);
    assert(m1[0] == 3);
    assert(m1[1] == 1);
    assert(m1.size() == 2);
    assert(m1.capacity() == 2);    
    
    assert(m == m1);
    m.clear();
    assert(m.size() == 0);
    
    assert(m1.size() == 2);
    m1.pop_back();
    assert(m1.size() == 1);

    try{
        int x =m1[2];
    }

    catch(out_of_range &e) {
        assert((string)e.what() == "out of bounds");
    }

    assert(m1.capacity() == 2);
    m1.reserve(8);
    assert(m1.capacity() == 8);

    myvector<int> m2((myvector<int>&&) m1);
    assert(m1.size() == 0);
    assert(m1.capacity() == 0);
    assert(m2.size() == 1);
    assert(m2.capacity() == 8);

    m2.push_back(5);
    m2.push_back(4);
    m2.push_back(3);
    m2.push_back(2);
    m2.push_back(1);
    m2.push_back(0);

    int i = 0;
    myvector<int>::iterator it;
    m2.begin();

    for(it = m2.begin(); it != m2.end(); it++) {
        assert(*it == m2[i]);
        i++;
    }
    assert(i == 6);

    return 0;
}
