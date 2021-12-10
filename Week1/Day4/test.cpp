#include <cassert>
#include <iostream>

using namespace std;

int main() {
    // 1. Arithmetic Expressions
    assert(3 == 3.0); 
    //float x = 3.1; 
    //assert(x == 3.1); 
    assert(3.1 == 3.1); 
    assert(true == 1.0); 
    assert('a' == 97); 
    int* p = 0; 
    assert(NULL == p); 
    //assert(NULL == 0); //this is the only line that fails

    // 2. Truth Table for Cast Operators
    cout << "int + float: " << 1 + 1.2 << endl;
    cout << "int + char: " << (1 + 'a') << endl;
    cout << "int + bool: " << (1 + true) << endl;
    cout << "bool + float: " << (true + 1.1) << endl;
    cout << "bool + char: " << true + 'a' << endl;
    cout << "float + char: " << 1.5 + 'a' << endl;

    return 0;
}