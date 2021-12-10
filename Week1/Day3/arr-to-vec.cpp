#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int arr_size =  3;

    float arr[3] = { 1.2, 2.4, 3.5 };

    //copies the array elements by referencing their distance from base pointer
    vector<float> vec(arr + 0, arr + arr_size);

    cout << "[ ";
    for(int i = 0; i < vec.size(); i++) {
        cout << vec.at(i) << " ";
    }
    cout << "]" << endl;

    for(int i = 0; i < vec.size(); i++) {
        assert(arr[i] == vec.at(i));
    }

    return 0;
}