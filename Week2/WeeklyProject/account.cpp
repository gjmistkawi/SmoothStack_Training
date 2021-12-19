#include "headers/account.h"

Account::Account() {
    vector<Transaction*>* _transactions = new vector<Transaction*>();
}

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

    _dollars = 0;
    _cents = 0;
    _transactions = new vector<Transaction*>();
}

Account::Account(int accountNum, string ssn, string firstName,
                 string lastName, string openDate, long dollars,
                 long cents, vector<Transaction*>* transactions) {
    _accountNum = accountNum;
    _ssn = ssn;
    _firstName = firstName;
    _lastName = lastName;
    _openDate = openDate;
    _dollars = dollars;
    _cents = cents;
    _transactions = transactions;
}

Account::~Account() {
    for(auto &(transaction) : *_transactions)
        delete transaction;

    _transactions->clear();
    delete _transactions;
}


// Operators

bool Account::operator==(const Account &acc) {
    return (acc.getSSN() == _ssn && acc.getFirstName() == _firstName && acc.getLastName() == _lastName);
}


// Getters

int Account::getAccountNum() const {
    return _accountNum;
}

string Account::getFirstName() const {
    return _firstName;
}

string Account::getLastName() const {
    return _lastName;
}

string Account::getSSN() const {
    return _ssn;
}

string Account::getBalance() const {
    string spacer = (_cents < 10) ? "0" : "";
    return "$" + to_string(_dollars) + "." + spacer + to_string(_cents);
}

string Account::getOpenDate() const {
    return _openDate;
}

long Account::getDollars(void) const {
    return _dollars;
}

long Account::getCents(void) const {
    return _cents;
}

vector<Transaction*>* Account::getTransactions() {
    return _transactions;
}


// Printing

string Account::displayAccount() {
    return "Customer Name: " + _firstName + " " + _lastName + "\n"
         + "SSN: ***-**-" + _ssn.substr(_ssn.size() - 4) + "\n"
         + "Date Opened: " + _openDate + "\n"
         + "Account: " + to_string(_accountNum) + "\n"
         + "Balance: " + getBalance() + "\n";
}

string Account::showAccount() {
    return _firstName + " " + _lastName + ", " + to_string(_accountNum) + ", " + _openDate;
}


// Transaction logic

bool Account::confirmTransaction(Transaction* transaction) {
    long type = (transaction->getTransactionType() == Transaction::Transaction_Type::debit) ? -1 : 1;
    long cents = _cents + (type * transaction->getCents());
    long dollars = _dollars + (type * transaction->getDollars());

    if(type == -1 && cents < 0) {
        dollars -= 1;
        cents += 100;
    } else if(type == 1 && cents >= 100) {
        dollars += 1;
        cents -= 100;
    }

    if(type == -1 && dollars < 0) return false; //transaction fails because balance insufficient for withdrawl

    _dollars = dollars;
    _cents = cents;
    _transactions->push_back(transaction);
    return true;
}