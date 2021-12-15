#include "headers/account.h"

Account::Account(int accountNum, string ssn, string firstName, string lastName) {
    _accountNum = accountNum;
    _ssn = ssn;
    _firstName = firstName;
    _lastName = lastName;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    _openDate = to_string(ltm->tm_mon + 1) + "/"
            + to_string(ltm->tm_mday) + "/"
            + to_string(ltm->tm_year + 1900);
}

//getters
int Account::getAccountNum() {
    return _accountNum;
}

string Account::getFirstName() {
    return _firstName;
}

string Account::getLastName() {
    return _lastName;
}

string Account::getSSN() {
    return _ssn;
}

//to string method?
string Account::displayAccount() {
    return "Customer Name: " + _firstName + " " + _lastName + "\n"
         + "SSN: ***-**-" + _ssn.substr(_ssn.size() - 4) + "\n"
         + "Date Opened: " + _openDate + "\n"
         + "Account: " + to_string(_accountNum) + "\n";
}

string Account::showAccount() {
    return _firstName + " " + _lastName + ", " + to_string(_accountNum) + ", " + _openDate;
}