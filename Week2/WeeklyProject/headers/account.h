#ifndef __account_h__
#define __account_h__

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "transaction.h"

using namespace std;

class Account {
    private:
        int     _accountNum;
        string  _ssn;
        string  _firstName;
        string  _lastName;
        string  _openDate;
        long    _dollars;
        long    _cents;
        
        vector<Transaction*>* _transactions;

    public:
        Account(void);
        Account(int,string,string,string);
        Account(int,string,string,string,string,long,long,vector<Transaction*>*);
        ~Account(void);

        // Operators
        bool operator==(const Account &acc);

        // Getters
        int     getAccountNum(void) const;
        string  getFirstName(void) const;
        string  getLastName(void) const;
        string  getSSN(void) const;
        string  getBalance(void) const;
        string  getOpenDate(void) const;
        long    getDollars(void) const;
        long    getCents(void) const;
        vector<Transaction*>* getTransactions(void);

        // Printing methods
        string  displayAccount(void);
        string  showAccount(void);

        // Transaction logic
        bool    confirmTransaction(Transaction*);

};

#endif