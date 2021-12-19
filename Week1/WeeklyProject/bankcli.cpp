#include <iostream>
#include "headers/bank.h"
#include "headers/transaction.h"

#define LOG_DISPLAY_COUNT 5

using namespace std;

// Temporary/false functions
Bank* bank;
Bank* falseRecords();
void  cleanFalseRecords();

void showAccounts();
void displayAccount();
bool addTransaction(int);
void displayTransactions(int);
void searchName();
void newAccount();
void closeAccount();
void displayOptions();
void displayLogs();


int main() {
    falseRecords();
    string input, pass;
    bool loggedIn = false;


    // Login loop
    while(!loggedIn) {
        cout << "user: ";
        getline(cin, input);
        cout << "password: ";
        getline(cin, pass);
        loggedIn = bank->userLogin(input, pass);
        if(!loggedIn) 
            cout << bank->logError("Incorrect user") << endl;
        cout << endl;
    }

    displayOptions();

    // Main loop
    while(input != "quit") {
        cout << "home > ";      // Print prompt
        getline(cin, input);    // Grab user input

        // Parsing input, redirecting flow
        if(input == "show accounts") {
            showAccounts();
        } else if(input == "display account") {
            displayAccount();
        } else if(input == "search name") {
            searchName();
        } else if(input == "new account") {
            newAccount();
        } else if(input == "close account") {
            closeAccount();
        } else if(input == "display logs") {
            displayLogs();
        } else if(input == "help") {
            displayOptions();
        } else if(input != "quit") {
            cout << bank->logError("Invalid command") << endl;
        }
    }

    cleanFalseRecords();
    return 0;
}

// Menu functions

void showAccounts() {
    vector<string> accounts = bank->showAccounts();
    
    for(int i = 0; i < accounts.size(); i++) {
        cout << accounts[i] << endl;
    }
    cout << endl;
}

void displayAccount() {
    string str;
    int accountNum;

    while(true) {
        cout << "account > ";
        getline(cin, str);
        
        int accountNum = stoi(str);
        str = bank->displayAccount(accountNum);
        if(str.empty())
            throw invalid_argument("No account found");

        cout << str << endl << endl;

        cout << "Options: " << endl;
        cout << "add transaction" << endl;
        cout << "display transactions" << endl;
        cout << "home" << endl;

        cout << "account > ";
        getline(cin, str);

        if(str == "add transaction") {
            if(addTransaction(accountNum))
                cout << "New Balance: " << bank->getAccountBalance(accountNum) << endl << endl;
            else
                cout << bank->logError("Insufficient balance") << endl << endl;
        }

        else if(str == "display transactions") {
            displayTransactions(accountNum);
            return;
        }

        else {
            cout << endl;
            return;
        }
    }
}

bool addTransaction(int accountNum) {
    string input;
    long cents, dollars;
    Transaction::Transaction_Type type;

    cout << "Amount: ";
    getline(cin, input);

    int split = input.find(".");
    string temp = input.substr(0, split);
    dollars = stol(temp);
    temp = input.substr(split + 2, input.size()-1);
    cents = stol(temp);

    
    cout << "debit/credit: ";
    getline(cin, input);

    if(input == "debit")
        type = Transaction::Transaction_Type::debit;
    else if(input == "credit")
        type = Transaction::Transaction_Type::credit;
    else {
        cout << bank->logError("Invalid transaction type") << endl << endl;
        return false;
    }

    Transaction* transaction = new Transaction(dollars, cents, type);
    return bank->addTransaction(accountNum, transaction);
}

void displayTransactions(int accountNum) {
    cout << "Transactions: " << endl;
    string message = bank->getAccountTransactions(accountNum);
    message = (message == "") ? "No transactions \n" : message;
    cout << message << endl;
}

void searchName() {
    string name;

    while(true) {
        cout << "name > ";
        getline(cin, name);

        // Validate name
        if(name.size() == 0) {
            cout << bank->logError("No name entered") << endl;
            return;
        }

        for(int i = 0; i < name.size(); i++) {
            if(!isalpha(name[i]) && !isspace(name[i]) && name[i]) {
                cout << bank->logError("Names may only contain letters and spaces") << endl << endl;
                return;
            }
        }

        // Return if home entered
        if(name == "Home")
            return;

        // Search name in bank
        int split = name.find(" ", 0);
        vector<tuple<string,int>> results = bank->searchName(name.substr(0,split), name.substr(split+1));

        // Display results
        int size = results.size();
        for(int i = 0; i < size; i++) {
            cout << i+1 << ". " << get<0>(results[i]) << endl;
        }
        cout << size+1 << ". Home" << endl;

        // Pick result
        int input;
        cout << "Select number > ";
        cin >> input;

        // Solves a cin buffer issue
        cin.clear();
        cin.ignore(10000,'\n');


        // Display selected account
        if((int)input <= results.size()) {
           string display = bank->displayAccount(get<1>(results[input-1]));
           cout << display << endl;
           return;
        }

        // Number for home selected
        else if((int)input == (results.size()+1)) {
            cout << endl;
            return;
        }

        else {
            cout << bank->logError("Invalid number") << endl;
        }
    }

}

void newAccount() {
    string name, ssn;

    cout << "Customer Name > ";
    getline(cin, name);

    // Validate name
    if(name.size() == 0) {
        cout << bank->logError("No name entered") << endl;
        return;
    }

    for(int i = 0; i < name.size(); i++) {
        if(!isalpha(name[i]) && !isspace(name[i]) && name[i]) {
            cout << bank->logError("Name may only contain letters and spaces") << endl << endl;
            return;
        }
    }

    cout << "SSN > ";
    getline(cin, ssn);

    //validate ssn
    if(ssn.size() != 9) {
        cout << bank->logError("Must be a valid SSN") << endl << endl;
        return;
    }

    for(int i = 0; i < ssn.size(); i++) {
        if(!isdigit(ssn[i])) {
            cout << bank->logError("SSN must be a valid number") << endl << endl;
            return;
        }
    }


    // Split name for account creation
    int split = name.find(" ", 0);
    int code = bank->createAccount(ssn, name.substr(0,split), name.substr(split+1));

    if(code == ERROR_ACCOUNT_EXISTS)
        cout << bank->logError("Account exists") << endl << endl;
    else
        cout << "New account number: " << code << endl << endl;
}

void closeAccount() {
    string input;
    cout << "account > ";
    getline(cin, input);

    try {
        int num = stoi(input);
        num = bank->closeAccount(num);
        if(num == ERROR_NO_ACCOUNT)
            cout << bank->logError("Invalid account") << endl << endl;
        else if(num == ERROR_DELETION_CANCEL)
            cout << bank->logError("Account closure cancelled") << endl << endl;
        else
            cout << "Account closed sucessfully" << endl << endl;
    }

    catch(exception e) {
        cout << bank->logError("Invalid account number") << endl << endl;
    }

}

void displayOptions() {
    cout << "Commands: " << endl;
    cout << "show accounts" << endl;
    cout << "display account" << endl;
    cout << "search name" << endl;
    cout << "new account" << endl;
    cout << "close account" << endl;
    cout << "display logs" << endl;
    cout << "help" << endl;
    cout << "quit" << endl;
    cout << endl;
}

void displayLogs() {
    cout << "Error logs: " << endl;
    for(auto log : bank->showErrorLog(LOG_DISPLAY_COUNT))
        cout <<  log << endl;
    cout << endl;
}

// False Records and temporary functions

Bank* falseRecords() {
    bank = new Bank();
    int temp;

    bank->createUser("guest", "password");

    temp = bank->createAccount("123456789", "George", "Mist");
    temp = bank->createAccount("987654321", "Bob", "Meow");
    temp = bank->createAccount("123454321", "Bobbert", "Meowth");


    return bank;
}

void cleanFalseRecords() {
    delete bank;
}