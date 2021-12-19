#ifndef __bank_h__
#define __bank_h__

#include <map>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "user.h"
#include "account.h"
#include "../bank.pb.h"


#define MAX_ACCOUNT_NUM         1000
#define ERROR_NO_ACCOUNT        -1
#define ERROR_DELETION_CANCEL   -2
#define ERROR_ACCOUNT_EXISTS    -3

 
using namespace std;

class Bank {
    private:
        map<int,Account*>*  _allAccounts; //should use a map?
        map<string,User*>*  _allUsers;
        vector<string>*     _errorLog;

        int  generateAccountNumber(void);

    public:
        Bank(void);
        Bank(map<int,Account*>*,map<string,User*>*,vector<string>*);
        ~Bank(void);

        // Account interactions
        int createAccount(string, string, string);
        int closeAccount(int);
        bool addTransaction(int,Transaction*);
        string getAccountBalance(int);
        string getAccountTransactions(int);
        vector<tuple<string,int>> searchName(string,string);

        // Account displays
        string displayAccount(int);
        vector<string> showAccounts(void);

        // User interactions
        bool createUser(string,string);
        bool userLogin(string,string);

        // Error Log
        string logError(string);
        vector<string> showErrorLog(int);

        // Data storing
        BANK::Bank* saveBankData(void);
};

#endif