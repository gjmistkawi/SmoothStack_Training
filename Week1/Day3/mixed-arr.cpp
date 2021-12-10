#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {

    // 2.1 - Dissimilar Arrays
    int i = 3, j = 5;
    float k = 3.8, l = 4.5;
    void* arr[4] = {&i, &j, &k, &l};

    assert(*(int*)arr[0] == 3);
    assert(*(int*)arr[1] == 5);
    // ODD ERROR - this assertion fails even though the value is correct when printed.
    // Unsure what is going on because the next assertion works just fine
    assert(*(float*)arr[2] == 3.8);
    //cout << *(float*)arr[2] << endl;
    assert(*(float*)arr[3] == 4.5);

    cout << "2.1 - Dissimilar Arrays" << endl;
    cout << "All elements of the mixed array were correct" << endl;
    cout << "[ 3 5 3.7 4.5 ]" << endl;

    // 2.2 - Types in Array
    cout << "2.2 - Types in Array" << endl;
    cout << "You cannot auto-detect the type of a void* and to try would break this program." << endl;

    return 0;
}