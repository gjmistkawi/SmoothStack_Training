#include <iostream>
#include "bank.h"

using namespace std;

// Temporary/false functions
Bank* bank;
Bank* falseRecords();
void  cleanFalseRecords();

void showAccounts();
void displayAccount();
void searchName();
void newAccount();
void closeAccount();
void displayOptions();


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
            cout << "Incorrect user" << endl;
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
        } else if(input == "help") {
            displayOptions();
        } else if(input != "quit") {
            cout << "Invalid command" << endl;
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
    cout << "account > ";
    getline(cin, str);
    
    try {
        int num = stoi(str);
        str = bank->displayAccount(num);
        if(str.empty())
            throw invalid_argument("No account found");

        cout << str << endl;
    }

    catch(exception e) {
        cout << "Invalid account" << endl << endl;
    }
}

void searchName() {
    string name;

    while(true) {
        cout << "name > ";
        getline(cin, name);

        // Validate name
        if(name.size() == 0) {
            cout << "No name entered" << endl;
            return;
        }

        for(int i = 0; i < name.size(); i++) {
            if(!isalpha(name[i]) && !isspace(name[i]) && name[i]) {
                cout << "Names may only contain letters and spaces" << endl << endl;
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
            cout << "Invalid number" << endl;
        }
    }

}

void newAccount() {
    string name, ssn;

    cout << "Customer Name > ";
    getline(cin, name);

    // Validate name
    if(name.size() == 0) {
        cout << "No name entered" << endl;
        return;
    }

    for(int i = 0; i < name.size(); i++) {
        if(!isalpha(name[i]) && !isspace(name[i]) && name[i]) {
            cout << "Name may only contain letters and spaces" << endl << endl;
            return;
        }
    }

    cout << "SSN > ";
    getline(cin, ssn);

    //validate ssn
    if(ssn.size() != 9) {
        cout << "Must be a valid SSN" << endl << endl;
        return;
    }

    for(int i = 0; i < ssn.size(); i++) {
        if(!isdigit(ssn[i])) {
            cout << "SSN must be a valid number" << endl << endl;
            return;
        }
    }


    // Split name for account creation
    int split = name.find(" ", 0);
    int code = bank->createAccount(ssn, name.substr(0,split), name.substr(split+1));

    if(code == ERROR_SOCIAL_IN_USE)
        cout << "Account exists - social in use" << endl << endl;
    else if(code == ERROR_NAME_IN_USE)
        cout << "Account exists - name in use" << endl << endl;
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
            cout << "Invalid account" << endl << endl;
        else if(num == ERROR_DELETION_CANCEL)
            cout << "Account closure cancelled" << endl << endl;
        else
            cout << "Account closed sucessfully" << endl << endl;
    }

    catch(exception e) {
        cout << "Invalid account number" << endl << endl;
    }

}

void displayOptions() {
    cout << "Commands: " << endl;
    cout << "show accounts" << endl;
    cout << "display account" << endl;
    cout << "search name" << endl;
    cout << "new account" << endl;
    cout << "close account" << endl;
    cout << "help" << endl;
    cout << "quit" << endl;
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