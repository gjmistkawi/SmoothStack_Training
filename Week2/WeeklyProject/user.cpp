#include "headers/user.h"

User::User(string userName, string password) {
    _userName = userName;
    _password = password;
}

string User::getUserName() {
    return _userName;
}

bool User::login(string password) {
    return (password == _password) ? true : false;
}