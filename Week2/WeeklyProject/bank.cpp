#include "headers/bank.h"

Bank::Bank() {
    _allAccounts = new map<int,Account*>();
    _allUsers = new map<string,User*>();
}

Bank::~Bank() {
    // Clean up accounts
    for(auto &account : *_allAccounts) {
        delete account.second;
    }
    
    delete _allAccounts;

    // Clean up users
    for(auto &user : *_allUsers) {
        delete user.second;
    }

    delete _allUsers;
}


// Account interactions

int Bank::createAccount(string ssn, string fName, string lName) {
    // Check if full name or ssn is in use
    for(auto &account : *_allAccounts) {
        if(account.second->getSSN() == ssn)
            return ERROR_SOCIAL_IN_USE;
        if(account.second->getFirstName() == fName && account.second->getLastName() == lName)
            return ERROR_NAME_IN_USE;
    }

    int accountNum = generateAccountNumber();
    Account* acc = new Account(accountNum, ssn, fName, lName);
    _allAccounts->insert({accountNum, acc});
    return acc->getAccountNum();
}

int Bank::closeAccount(int accountNum) {
    string input;
    auto iter = _allAccounts->find(accountNum);

    // No account found with matching accountNum
    if(iter == _allAccounts->end()) return ERROR_NO_ACCOUNT;

    cout << "Do you want to close acount " << iter->second->getAccountNum() << "? (yes/no)" << endl;
    cout << "account > ";
    getline(cin, input);

    // User does not want to delete
    if(input != "yes") return ERROR_DELETION_CANCEL;

    delete iter->second;
    _allAccounts->erase(accountNum);
    return 0;
}


// Display functions

string Bank::displayAccount(int accountNum) {
    auto iter = _allAccounts->find(accountNum);

    // No account found
    if(iter == _allAccounts->end()) return NULL;

    return iter->second->displayAccount();
}

vector<string> Bank::showAccounts() {
    vector<string> accounts = vector<string>();

    for(auto &account : *_allAccounts) {
        accounts.push_back(account.second->showAccount());
    }

    return accounts;
}

vector<tuple<string,int>> Bank::searchName(string fName, string lName) { 
    //substring and then length!
    vector<tuple<string,int>> results = vector<tuple<string,int>>();
    vector<int> resultDrift = vector<int>();
    int drift = 0; //drift from searched term, 0 is perfect match
    int i = 0;

    for(auto &account : *_allAccounts) {
        drift = 0;
        
        //match last name
        string str = account.second->getLastName();
        if(str.find(lName) != string::npos) {
            drift += str.size() - lName.size();

            //match first name
            str = account.second->getFirstName();
            if(str.find(fName) != string::npos) {
                drift += str.size() - fName.size();

                //order vectors by drift value
                for(i = 0; i < resultDrift.size(); i++){
                    if(resultDrift[i] > drift)
                        break;
                }

                //add current drift to ith position of drift vector
                resultDrift.insert(resultDrift.begin() + i, drift);
                results.insert(results.begin() + i, tuple<string,int>(account.second->getFirstName() + " " 
                                                                    + account.second->getLastName(),
                                                                      account.first));
            }
        }
    }

    return results;
}


// User interactions

bool Bank::createUser(string name, string password) {
    auto iter = _allUsers->find(name);
    if(iter != _allUsers->end()) return false;   // User already exists

    User* user = new User(name, password);
    _allUsers->insert({name, user});
    return true;
}

bool Bank::userLogin(string name, string password) {
    auto iter = _allUsers->find(name);
    if(iter == _allUsers->end()) return false;   // User does not exist
    
    return iter->second->login(password);
}

// Private function

int Bank::generateAccountNumber() {
    int accountNum;
    srand(time(NULL));

    while(true) {
        accountNum = (rand() % MAX_ACCOUNT_NUM) + 1;   //account numbers from 1 to 1000
        auto iter = _allAccounts->find(accountNum);
        if(iter == _allAccounts->end())
            return accountNum;
    }
}

