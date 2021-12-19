#include "headers/transaction.h"

Transaction::Transaction(long dollars, long cents, Transaction_Type type) {
    _dollars = dollars;
    _cents = cents;
    _type = type;
}

long Transaction::getDollars(void) {
    return _dollars;
}

long Transaction::getCents(void) {
    return _cents;
}

Transaction::Transaction_Type Transaction::getTransactionType() {
    return _type;
}

string Transaction::printTransaction(void) {
    string symbol = (_type == Transaction_Type::debit) ? "-" : "+";
    string spacer = (_cents < 10) ? "0" : "";
    return symbol + " $" + to_string(_dollars) + "." + spacer + to_string(_cents);
}