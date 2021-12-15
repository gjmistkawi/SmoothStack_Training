#include <iostream>
#include <cassert>

using namespace std;

//Fun solultion here: basically because of binary math, if num
//is a power of 2, then it will not have a value in the 1's place.
//So if you subtract 1, then it flips all the bits, and when you &
//the solution, then you end up with 0 because there should be no 
//bits that are the same. The edge cases are 0 and 1, which are checked.

bool powerOfTwo(int num) {
    return num != 0 && num != 1 && !(num & (num-1));
}


int main() {
    int num;
    cout << "Enter number: ";
    cin >> num;

    bool isPower = powerOfTwo(num);

    cout << num << " " << ((isPower) ? "is" : "is not");
    cout <<  " a power of 2" << endl;

    assert(powerOfTwo(2) == true);
    assert(powerOfTwo(0) == false);
    assert(powerOfTwo(-4) == false);
    assert(powerOfTwo(15) == false);
    assert(powerOfTwo(16) == true);


    //for(int i = 0; i < 10000; i++) {
    //    if(powerOfTwo(i))
    //        cout << i << ", ";
    //}
    //cout << endl;

    return 0;
}