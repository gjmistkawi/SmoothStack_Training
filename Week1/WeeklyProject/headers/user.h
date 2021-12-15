#ifndef __user_h__
#define __user_h__

#include <string>

using namespace std;

class User {
    private:
        string _userName;
        string _password;

    public:
        User(void);
        User(string, string);
        //~User(void);

        //login functions
        string  getUserName();
        bool    login(string);
};


#endif
