#include <iostream>
#include <string>
#include "person.h"

using namespace std;

#define MAX_NAMES 7

int main(void) {
    // declare and string array of names here
    string names[MAX_NAMES] = {"bob", "james", "janet", "bob", "stella", "bob", "stella"};
    Person* person;
    
    cout << "Making the following persons: " << endl;
    cout << "{\"bob\", \"james\", \"janet\", \"bob\", \"stella\", \"bob\", \"stella\"}" << endl << endl;

    for (int i = 0; i < MAX_NAMES; i++) {
        person = new Person(names[i]);
    }

    cout << "{";
    for (int i = 0; i < MAX_NAMES; i++) {
        if(Person::persons[i] == nullptr) 
            break;
        
        cout << " " << Person::persons[i]->name << ": " << Person::persons[i]->count << ",";
    }
    cout << "\b" << " }" << endl;
}