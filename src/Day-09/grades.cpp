#include <iostream>
#include <cassert>
#include <map>

using namespace std;


class Grade {
    static const map<int,char> grades;

    public:
        static char grade(const int&& score) {
            //for(auto iter = grades.find(score); iter != grades.end(); iter++)
            return (grades.find(score))->second;
        }
};

const map<int,char> Grade::grades = {{{40, 'A'}, {30, 'B'}, {20, 'C'}, {10, 'D'}, {0, 'F'}}};


int main(void) {
    /*
        Generate an array with N=4 values eg. {10, 30, 20, 20}
        Write a loop that loops through the array, and calls the method above.
        You are not allowed to use any if/else statements.
        You print the result of the method using cout.
    */
    int grades[4] = {10,20,30,40};
    //Grade* g = new Grade();

    for(int i = 0; i < sizeof(grades)/sizeof(int); i++) {
        cout << "Score = " << grades[i] << ": Grade " << Grade::grade((const int)grades[i]) << endl;
    }

    assert(Grade::grade(30 == 'B'));
    assert(Grade::grade(40 == 'A'));
    assert(Grade::grade(10 == 'D'));
    assert(Grade::grade(20 == 'C'));
    assert(Grade::grade(0  == 'F'));


    return 0;
}