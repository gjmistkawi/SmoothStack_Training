#include <iostream>

using namespace std;

void fibonacci(long,const long,long*);

int main() {
    long number = 50;
    long* arr = new long[number];
    fibonacci(number, (const long)(number-1), arr);
    
    for(long i = 0; i < number; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}

void fibonacci(long index, const long size, long* arr) {
    long curr_index = size - index;
    if(curr_index < 2)
        arr[curr_index] = 1;
    else
        arr[curr_index] = arr[curr_index-1] + arr[curr_index-2]; 

    if(curr_index < size)
        fibonacci(index-1, size, arr);
}