#include "mystring.h"

MyString::MyString(char* s) {
    data = new char[strlen(s)];
    strcpy(data, s);
}

MyString::~MyString() {
    delete data;
}

//deep copy const
MyString::MyString(const MyString& copy) {
    data = new char[strlen(copy.getData())];
    strcpy(data, copy.getData());
}

//deep copy operator
MyString& MyString::operator=(const MyString& copy) {
    data = new char[strlen(copy.getData())];
    strcpy(data, copy.getData());
}

//move constructor
MyString::MyString(MyString&& move) {
    data = move.data;
    move.data = nullptr;
}

//move operator
MyString& MyString::operator= (MyString&& move) {
    if(this == &move) return *this;

    if(data != nullptr)
        delete data;
    
    data = move.data;
    move.data = nullptr;

    return *this;
}

const char* MyString::getData() const {
    return data;
}

//operators

//adding 2 strings together
char* MyString::operator+ (const MyString& s) {
    char* temp = new char[strlen(data) + strlen(s.getData()) - 1]; //-1 to cut a \0 char

    temp[0] = '\0'; //need to initialize to blank string for cat
    strcat(temp, data);
    strcat(temp, s.getData());

    return temp;
}

//changing the position of the string?
char* MyString::operator+ (const int i) {
    int length = strlen(data) - i + 1;
    char* temp = new char[length];
    
    for(int j = 0; j < length-1; j++) {
        temp[j] = data[j + i];
    }

    temp[length] = '\0';

    return temp;
}


//replicates the string i times
char* MyString::operator* (const int i) {
    int length = strlen(data) * i + 1;
    char* temp = new char[length];
    temp[0] = '\0';

    for(int j = 0; j < i; j++) {
        strcat(temp, data);
    }

    temp[length] = '\0';

    return temp;
}

//access an element of string
char  MyString::operator[] (const int i) {
    return data[i];
}