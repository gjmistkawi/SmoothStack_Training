#include "person.h"

Person::Person(string name) {
    this->name = name;
    count = 1;

    Person* exists = getPerson(name);

    if(exists == nullptr) {
        for(int i = 0; i < MAX_PERSONS; i++) {
            if(persons[i] == nullptr) {
                persons[i] = this;
                index = i;
                break;
            }
        }
    } 
    
    else {
        count += exists->count;
        index = exists->index;
        persons[index] = this;
        delete exists;
    }
}


Person* Person::getPerson(string name) {
    for(int i = 0; i < MAX_PERSONS; i++) {
        if(persons[i] == nullptr)
            break;
            
        if(persons[i]->name == name)
            return persons[i];
    }

    return nullptr;
}