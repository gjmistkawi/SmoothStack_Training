#ifndef __account_h__
#define __account_h__

#include<iostream>
#include <string>
#include <ctime>

using namespace std;

class Account {
    private:
        int     _accountNum;
        string  _ssn;
        string  _firstName;
        string  _lastName;
        string  _openDate;

    public:
        Account(void);
        Account(int,string,string,string);
        //~Account(void);

        //getters
        int     getAccountNum();
        string  getFirstName();
        string  getLastName();
        string  getSSN();

        //to string method?
        string  displayAccount();
        string  showAccount();
};


#endif
