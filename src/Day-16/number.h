#ifndef __number_h__
#define __number_h__

#include <string>
#include <sstream>
#include <bitset>
//#include <iomanip>

class Number {
private:
    std::string err = "Invalid Number";
    unsigned int num;

    unsigned int parseBinary(std::string s);
    unsigned int parseHex(std::string s);

public:
    Number(std::string s);

    Number& operator+(const Number &n);

    std::string asDecimal(void);
    std::string asBinary(void);
    std::string asHex(void);
};

#endif