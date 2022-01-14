#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>
#include "number.h"

using std::string;
using std::cout;

string parseInput(string input);

int main(void) {
    bool quit = false;

    while(!quit) {
        cout << "prompt > ";
        string input;
        getline(std::cin, input);

        if(input == "quit" || input == "exit")
            quit = true;
        
        else {
            cout << std::right << std::setw(20) << parseInput(input) << std::endl;
        }
    }

    return 0;
}

string parseInput(string input) {
    std::vector<string> v;
    string data, output;
    int x,y;

    std::stringstream parse(input);
    std::stringstream ss;

    while(parse >> data)
        v.push_back(data);

    try {
        if(v.size() == 3 && v.at(1) == "+") {
            Number n = Number(v.at(0)) + Number(v.at(2));
            output = n.asDecimal();
        }
        //output = (Number(v.at(0)) + Number(v.at(2))).asDecimal();

        else if(v.size() == 2) {
            if(v.at(0) == "hex")
                output = Number(v.at(1)).asHex();
            else if(v.at(0) == "bin")
                output =  Number(v.at(1)).asBinary();
            else
                throw std::invalid_argument("Invalid Option");
        }

        else if(v.size() == 1)
            output = Number(v.at(0)).asDecimal();

        else
            throw std::invalid_argument("Invalid Option");


        cout << output << std::endl;
        return output;
    }


    catch(std::invalid_argument &e) {
        if(e.what() == "stoi")
            return "Invalid Number";
        return e.what();
    }

    catch(std::out_of_range &e) {
        return "Number out of bounds";
    }
}