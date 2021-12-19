#include "headers/user.h"


User::User(string userName, string password) {
    _userName = userName;
    _password = passwordHash((const string)password);
}

string User::getUserName() {
    return _userName;
}

bool User::login(string password) {
    return (passwordHash((const string)password) == _password) ? true : false;
}

// SHA 256 hash func
string User::passwordHash(const string pass) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, pass.c_str(), pass.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}