#include <cassert>
#include <iostream>
#include <string>
#include "sentence.h"

using namespace std;

int main(void) {
    string str = "Hello how are you?";
    char* sample = new char[str.size()];
    strcpy(sample, str.c_str());

    Sentence* s1 = new Sentence(sample);

    //testing basic functionality
    assert(s1->num_words() == 4); 
    assert(s1->get_word(2) == "how"); 
    assert(s1->data() == sample); 
    str = "Now we do something else.";
    sample = new char[str.size()];
    strcpy(sample, str.c_str());
    s1->replace(sample);
    assert(s1->num_words() == 5); 
    assert(s1->get_word(3) == "do"); 

    //copy constructor tests
    Sentence* s2 = new Sentence(*s1);

    assert(s2->num_words() == 5); 
    assert(s2->get_word(3) == "do");
    delete s1;
    assert(s2->num_words() == 5); 
    assert(s2->get_word(3) == "do");

    //copy assignment operator tests
    Sentence s3 = *s2;

    assert(s3.num_words() == 5); 
    assert(s3.get_word(3) == "do");
    delete s2;
    assert(s3.num_words() == 5); 
    assert(s3.get_word(3) == "do");

    //move constructor tests
    Sentence* s4 = new Sentence((Sentence&&)s3);
    assert(s3.data() == nullptr);
    assert(s4->num_words() == 5);
    assert(s4->get_word(3) == "do");

    //move assignment operator tests
    //s3 = (Sentence&&)s4;
    //assert(s4->data() == nullptr);
    //assert(s4->num_words() == 0);
    //assert(s3.num_words() == 5);
    //assert(s3.get_word(3) == "do");

    return 0;
}