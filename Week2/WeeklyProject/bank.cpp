#include "headers/bank.h"

Bank::Bank() {
    _allAccounts = new map<int,Account*>();
    _allUsers = new map<string,User*>();
    _errorLog = new vector<string>();
}

Bank::Bank(map<int,Account*>* allAccounts, map<string,User*>* allUsers, vector<string>* errorLog) {
    _allAccounts = allAccounts;
    _allUsers = allUsers;
    _errorLog = errorLog;
}

Bank::~Bank() {
    // Clean up accounts
    for(auto &account : *_allAccounts) {
        delete account.second;
    }
    
    // Clean up users
    for(auto &user : *_allUsers) {
        delete user.second;
    }

    delete _allAccounts;
    delete _allUsers;
    delete _errorLog;
}


// Account interactions

int Bank::createAccount(string ssn, string fName, string lName) {
    int accountNum = generateAccountNumber();
    Account* acc = new Account(accountNum, ssn, fName, lName);

    // Check if full name or ssn is in use
    for(auto &account : *_allAccounts) {
        if(*acc == *account.second) {
            delete acc;
            return ERROR_ACCOUNT_EXISTS;
        }
    }

    _allAccounts->insert({accountNum, acc});
    return acc->getAccountNum();
}

int Bank::closeAccount(int accountNum) {
    string input;
    auto iter = _allAccounts->find(accountNum);

    // No account found with matching accountNum
    if(iter == _allAccounts->end()) return ERROR_NO_ACCOUNT;

    cout << "Do you want to close account " << iter->second->getAccountNum() << "? (yes/no)" << endl;
    cout << "account > ";
    getline(cin, input);

    // User does not want to delete
    if(input != "yes") return ERROR_DELETION_CANCEL;

    delete iter->second;

    _allAccounts->erase(accountNum);
    return 0;
}

bool Bank::addTransaction(int accountNum, Transaction* transaction) {
    auto iter = _allAccounts->find(accountNum);
    return (iter->second->confirmTransaction(transaction)) ? true : false;
}

string Bank::getAccountBalance(int accountNum) {
    auto iter = _allAccounts->find(accountNum);
    return iter->second->getBalance();
}

string Bank::getAccountTransactions(int accountNum) {
    auto iter = _allAccounts->find(accountNum);
    vector<Transaction*>* transactions = iter->second->getTransactions();

    string message = "";
    for (auto transaction : *transactions) {
        message += transaction->printTransaction() + "\n";
    }

    return message;
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


// Error log

string Bank::logError(string error) {
    string message = "Log Entry " + to_string(_errorLog->size() + 1) + ": " + error;
    _errorLog->push_back(message);
    return message;
}

vector<string> Bank::showErrorLog(int length) {
    vector<string> errors;
    for(int i = 1; (((int)_errorLog->size() - i) >= 0) && (i < length); i++)
        errors.push_back(_errorLog->at(_errorLog->size() - i));

    return errors;
}


// Data Storing

BANK::Bank* Bank::saveBankData() {
    BANK::Bank* b = new BANK::Bank();

    // Save account info
    for(auto temp : *_allAccounts) {
        Account* a = temp.second;
        BANK::Account* acc = b->add_allaccounts();

        acc->set_accountnum(a->getAccountNum());
        acc->set_ssn(a->getSSN());
        acc->set_firstname(a->getFirstName());
        acc->set_lastname(a->getLastName());
        acc->set_opendate(a->getOpenDate());
        acc->set_dollars(a->getDollars());
        acc->set_cents(a->getCents());

        vector<Transaction*>* t = temp.second->getTransactions();
        for(auto transaction : *t) {
            BANK::Transaction* tran = acc->add_transactions();
            tran->set_cents(transaction->getCents());
            tran->set_dollars(transaction->getDollars());
            tran->set_type((BANK::Transaction_Transaction_Type)transaction->getTransactionType());
        }
    }

    for(auto temp : *_allUsers) {
        User* u = temp.second;
        BANK::User* user = b->add_allusers();
        
        user->set_username(u->getUserName());
        user->set_password(u->getHashPass());
    }


    for(auto error : *_errorLog) {
        BANK::Error* e = b->add_errorlog();
        e->set_error(error);
    }

    return b;
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