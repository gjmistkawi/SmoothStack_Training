#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <bitset>

using namespace std;

void parseInput(string input);
void stringToHex(string s);
void stringToBin(string s);
unsigned int* hexstringToInt(string s);
unsigned int* binstringToInt(string s);
void addInput(string s1, string s2);

int main(void) {
    bool quit = false;

    while(!quit) {
        cout << "prompt > ";
        string input;
        getline(cin, input);

        if(input == "quit" || input == "exit")
            quit = true;
        
        else {
            parseInput(input);
        }
    }

    return 0;
}

void parseInput(string input) {
    vector<string> v;
    string data, output;
    int x,y;

    stringstream parse(input);
    stringstream ss;

    while(parse >> data)
        v.push_back(data);


    if(v.size() == 3 && v.at(1) == "+")
        addInput(v.at(0), v.at(2));

    else if(v.size() == 2) {
        if(v.at(0) == "hex") {
            ss << hex << stoi(v.at(1));
            output = ss.str();
            cout << setfill(' ') << setw(20) << "0x" << output << endl;
        }

        else if(v.at(0) == "bin")
            stringToBin(v.at(1));
    }

    else if(v.size() == 1) {
        //is hex
        if(v.at(0).compare(0,2, "0x") == 0)
            stringToHex(v.at(0));

        //is binary
        else if(v.at(0).compare(0,2, "0b") == 0)
            stringToBin(v.at(0));
    }

}

void stringToHex(string s) {
    unsigned int* i;
    if(s.compare(0,2, "0b") == 0)
        i = binstringToInt(s.substr(2));
    else
        i = hexstringToInt(s);

    if(i == 0) {
        cout << setfill(' ') << setw(20) << "Invalid number" << endl;
        return;
    }

    cout << setfill(' ') << setw(20) << *i << endl; 
}

void stringToBin(string s) {
    unsigned int* i;
    if(s.compare(0,2, "0x") == 0)
        i = hexstringToInt(s);

    else {
        *i = stoi(s);
    }

    if(i == 0) {
        cout << setfill(' ') << setw(20) << "Invalid number" << endl;
        return;
    }

    string output = bitset<16>(*i).to_string();
    cout << setfill(' ') << setw(20) << "0b" << output << endl; 
}

unsigned int* hexstringToInt(string s) {
    // makes sure its a valid hex string
    string temp = s.substr(2);
    for(int i = 0; i < temp.size(); i++) {
        if(!isxdigit(temp[i]))
            return 0;
    }

    stringstream ss;
    unsigned int* i = new unsigned int();

    ss << hex << s;
    ss >> *i;

    return i;
}

unsigned int* binstringToInt(string s) {
    unsigned int* i = new unsigned int();
    *i = stoi(s, 0, 2);
    return i;
}

void addInput(string s1, string s2) {
    unsigned int x, y;

    if(s1.compare(0,2, "0x") == 0)
        x = *hexstringToInt(s1);
    else
        x = stoi(s1);

    if(s2.compare(0,2, "0x") == 0)
        y = *hexstringToInt(s2);
    else
        y = stoi(s2);

    cout << setfill(' ') << setw(20) << x+y << endl; 
}