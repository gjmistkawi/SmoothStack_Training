#ifndef __mystring_h__
#define __mystring_h__

#include "string.h"

class MyString {
private:
    char* data;

public:
    MyString(char* s);
    ~MyString();
    //copy
    MyString(const MyString& s);
    MyString& operator= (const MyString& s);
    //move
    MyString(MyString&& s);
    MyString& operator= (MyString&& s);

    const char* getData(void) const;

    char* operator+ (const MyString& s); //adding 2 strings together
    char* operator+ (const int i);   //changing the position of the string?
    char* operator* (const int i);   //replicates the string i times
    char  operator[] (const int i);  //access an element of string
};



/*


private:
    char* sentence;
    std::vector<int> vsentence; // stores the word offsets
    
public:
    Sentence(char* sent); // regular constructor

    //copy
    Sentence(Sentence& s); // deep copy  constructor
    Sentence& operator= (Sentence s); // deep copy assignment operator
    //move
    Sentence(Sentence&& s); // deep move constuctor
    Sentence& operator= (Sentence&& s);

    char* data() const; // returns the data for sentence
    int num_words() const; // fetches the number of words 
    std::string get_word(int n) const; // get nth word in sentence 
    void replace(char* sent); // replace existing sentence
    ~Sentence(); // destroy any memory allocated
};
*/
#endif