#ifndef __person_h__
#define __person_h__

#include <iostream>
#include <string>

using namespace std;

#define MAX_PERSONS 10

class Person {
    private:
        int index;
        
    public:
        Person(string name);
        //~Person();
        string name;
        int count;

        static inline Person* persons[MAX_PERSONS] {nullptr};
        static Person* getPerson(string name);
};

#endif