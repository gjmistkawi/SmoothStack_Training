#ifndef __bank_h__
#define __bank_h__

#include <map>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "user.h"
#include "account.h"

#define MAX_ACCOUNT_NUM         1000
#define ERROR_NO_ACCOUNT        -1
#define ERROR_DELETION_CANCEL   -2
#define ERROR_SOCIAL_IN_USE     -3
#define ERROR_NAME_IN_USE       -4

 
using namespace std;

class Bank {
    private:
        map<int,Account*>* _allAccounts; //should use a map?
        map<string,User*>* _allUsers;

        int  generateAccountNumber();

    public:
        Bank(void);
        ~Bank(void);

        // Account interactions
        int createAccount(string, string, string);
        int closeAccount(int);

        // Account displays
        string displayAccount(int);
        vector<string> showAccounts();
        vector<tuple<string,int>> searchName(string,string);

        // User interactions
        bool createUser(string,string);
        bool userLogin(string,string);
};


#endif
