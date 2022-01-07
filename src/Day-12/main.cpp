#include <cassert>
#include <iostream>
#include <string>
#include "mystring.h"

using namespace std;

int main(void) {
    string str1 = "abc";//"Hello how";
    string str2 = "def";//" are you?";

    char* cstr_1 = new char[str1.size()];
    strcpy(cstr_1, str1.c_str());

    char* cstr_2 = new char[str2.size()];
    strcpy(cstr_2, str2.c_str());

    MyString s1(cstr_1);
    MyString s2(cstr_2);

    // addition test
    assert((string)(s1 + s2) == "abcdef");

    // int addition test
    assert((string)(s1 + 1) == "bc");
    assert((string)(s2 + 2) == "f");

    // multiplacation test
    assert((string)(s1 * 2) == "abcabc");
    assert((string)(s2 * 3) == "defdefdef");

    // access test
    assert(s1[2] == 'c');
    assert(s2[0] == 'd');

    return 0;
}