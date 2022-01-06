#include "sentence.h"
#include <iostream>

using namespace std;

Sentence::Sentence(char* sent) {
    sentence = sent;

    // set first word starting at 0
    vsentence.push_back(0);

    // find the start of word based on space chars
    for(int i = 1; i < strlen(sentence); i++) {
        if(sentence[i-1] == ' ')
            vsentence.push_back(i);
    }
}

//deep copyz
Sentence::Sentence(Sentence& s) {
    sentence = new char[strlen(s.data())];
    strcpy(sentence, s.data());
    
    for(auto index: s.vsentence) {
        vsentence.push_back(index);
    }
}

// deep assignment
Sentence& Sentence::operator=(const Sentence s) {
    sentence = new char[strlen(s.data())];
    strcpy(sentence, s.data());

    for(auto index: s.vsentence) {
        vsentence.push_back(index);
    }

    return *this;
}

// move construction operator
Sentence::Sentence(Sentence&& s) {
    sentence = s.sentence;
    vsentence = s.vsentence;

    s.sentence = nullptr;
    s.vsentence.clear();
}

// move assignment operator
Sentence& Sentence::operator=(Sentence&& s) {
    if(this == &s) return *this;

    if(sentence != nullptr)
        delete sentence;
    vsentence.clear();

    sentence = s.sentence;
    vsentence = s.vsentence;

    s.sentence = nullptr;
    vsentence.clear();
    return *this;
}


char* Sentence::data() const {
    return sentence;
}

int Sentence::num_words() const {
    return vsentence.size();
}

string Sentence::get_word(int n) const {
    int start, end;
    char c;

    start = vsentence.at(n-1);

    if(n != this->num_words())
        end = vsentence.at(n) - 1;  // cust off the ' '
    else
        end = strlen(sentence) - 1;   //-2 to cut out \0 char?

    string result = "";

    for (int i = start; i < end; i++) {
        result += sentence[i];
    }


    return result;
}

void Sentence::replace(char* sent) {
    delete sentence;
    sentence = sent;

    vsentence.clear();
    vsentence.push_back(0);

    // find the start of word based on space chars
    for(int i = 1; i < strlen(sentence); i++) {
        if(sentence[i-1] == ' ')
            vsentence.push_back(i);
    }
}

Sentence::~Sentence() {
    delete sentence;
}