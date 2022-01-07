#ifndef __sentence_h__
#define __sentence_h__

#include <vector>
#include <string>
#include "string.h"

class Sentence {
private:
    char* sentence;
    std::vector<int> vsentence; // stores the word offsets
    
public:
    Sentence(char* sent); // regular constructor

    //copy
    Sentence(const Sentence& s); // deep copy  constructor
    Sentence& operator= (const Sentence& s); // deep copy assignment operator
    //move
    Sentence(Sentence&& s); // deep move constuctor
    Sentence& operator= (Sentence&& s);

    char* data() const; // returns the data for sentence
    int num_words() const; // fetches the number of words 
    std::string get_word(int n) const; // get nth word in sentence 
    void replace(char* sent); // replace existing sentence
    ~Sentence(); // destroy any memory allocated
};

#endif
