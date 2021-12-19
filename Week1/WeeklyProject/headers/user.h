#ifndef __user_h__
#define __user_h__

#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

// Add to compile:
// g++ -lcrypto main.cc

using namespace std;

class User {
    private:
        string _userName;
        string _password;

        string passwordHash(const string);

    public:
        User(void);
        User(string, string);
        //~User(void);

        //login functions
        string  getUserName(void);
        bool    login(string);
};


#endif
