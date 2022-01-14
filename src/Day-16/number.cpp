#include "number.h"

using std::string;

// private methods

unsigned int Number::parseBinary(string s) {
    return stoi(s, 0, 2);
}

unsigned int Number::parseHex(string s) {
    for(int i = 0; i < s.size(); i++) {
        if(!isxdigit(s[i]))
            throw std::invalid_argument(err);
    }

    std::stringstream ss;
    unsigned int i;

    ss << std::hex << s;
    ss >> i;

    return i;
}



// public methods

Number::Number(string s) {
    //int input
    if(s.size() > 2) {
        if(s.compare(0,2, "0x") == 0)
            num = parseHex(s.substr(2));
        else if(s.compare(0,2, "0b") == 0)
            num = parseBinary(s.substr(2));
        else
            num = stoi(s);
    }

    else
        num = stoi(s);
}

Number& Number::operator+(const Number &n) {
    this->num += n.num;
    return *this;
}

string Number::asDecimal(void) {
    return std::to_string(num);
}

string Number::asBinary(void) {
    return ("0b" + std::bitset<16>(num).to_string());
}

string Number::asHex(void) {
    std::stringstream ss;
    ss << std::hex << num;
    return ("0x" + ss.str());
}