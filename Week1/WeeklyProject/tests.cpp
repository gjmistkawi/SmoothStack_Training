#include <iostream>
#include <cassert>
#include "account.h"
#include "user.h"
#include "bank.h"

using namespace std;

void accountTests();
void userTests();
void bankTests();
void cliTests();

int main() {
    cout << "=============================" << endl;
    accountTests();
    cout << "=============================" << endl;
    userTests();
    cout << "=============================" << endl;
    bankTests();
    cout << "=============================" << endl;
    cliTests();
    cout << endl;

    return 0;
}

//=================================================
//==================== TESTS ======================
//=================================================

void accountTests() {
    cout << "Account Class Unit Testing" << endl;

    string fName = "George";
    string lName = "Mistk";
    string ssn = "123456789";
    int accNum = 1;
 
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(ltm->tm_mon + 1) + "/"
            + to_string(ltm->tm_mday) + "/"
            + to_string(ltm->tm_year + 1900);

    Account acc1 = Account(accNum, ssn, fName, lName);

    cout << "1) Getter tests" << endl;
    assert(fName == acc1.getFirstName());
    assert(lName == acc1.getLastName());
    assert(ssn == acc1.getSSN());

    cout << "2) Display tests" << endl;
    string display = "Customer Name: " + fName + " " + lName + "\n"
                    + "SSN: ***-**-" + ssn.substr(ssn.size() - 4) + "\n"
                    + "Date Opened: " + date + "\n"
                    + "Account: " + to_string(accNum) + "\n";

    string show = fName + " " + lName + ", " 
                    + to_string(accNum) + ", "
                    + date;

    assert(display == acc1.displayAccount());
    assert(show == acc1.showAccount());
}

void userTests() {
    cout << "User Class Unit Testing" << endl;

    string name = "Bobbert93";
    string password = "somerandompass";

    User user = User(name, password);

    cout << "1) Getter tests" << endl;
    assert(name == user.getUserName());

    cout << "2) Login tests" << endl;
    assert(user.login(password));
    assert(!user.login("wrongpassword"));
}

void bankTests() {
    cout << "Bank Class Unit Testing" << endl;
    Bank* bank = new Bank();

    // Fake person 1
    string fName1 = "George";
    string lName1 = "Mist";
    string ssn1 = "123456789";
    int accountNum1;

    // Fake person 2
    string fName2 = "Bob";
    string lName2 = "Meow";
    string ssn2 = "987654321";
    int accountNum2;

    // Fake person 3
    string fName3 = "Bobbert";
    string lName3 = "Meowth";
    string ssn3 = "123454321";
    int accountNum3;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(ltm->tm_mon + 1) + "/"
                + to_string(ltm->tm_mday) + "/"
                + to_string(ltm->tm_year + 1900);


    cout << "1) Account interaction tests" << endl;
    accountNum1 = bank->createAccount(ssn1, fName1, lName1);
    assert(accountNum1 > 0);    // No error messages on creation
    accountNum2 = bank->createAccount(ssn1, fName2, lName2);
    assert(accountNum2 == ERROR_SOCIAL_IN_USE); // SSN already in use
    accountNum2 = bank->createAccount(ssn2, fName1, lName1);
    assert(accountNum2 == ERROR_NAME_IN_USE);   // Name already in use
    accountNum2 = bank->createAccount(ssn2, fName2, lName2);
    assert(accountNum2 > 0);    // No error messages on creation
    assert(accountNum2 != accountNum1); // Accounts have different accountNum
    accountNum3 = bank->createAccount(ssn3, fName3, lName3);
    assert(!bank->displayAccount(accountNum3).empty());
    //assert(bank->closeAccount(accountNum3) == 0);   // Account deleted successfully
    //assert(bank->closeAccount(accountNum3) == ERROR_NO_ACCOUNT);    // No account found to delete
    //accountNum3 = bank->createAccount(ssn3, fName3, lName3);


    cout << "2) Account display tests" << endl;
    assert(bank->showAccounts().size() == 3); // Correct number of accounts displayed

    string display = "Customer Name: " + fName2 + " " + lName2 + "\n"
                    + "SSN: ***-**-" + ssn2.substr(ssn2.size() - 4) + "\n"
                    + "Date Opened: " + date + "\n"
                    + "Account: " + to_string(accountNum2) + "\n";   
    assert(display == bank->displayAccount(accountNum2));
    //assert search names

    cout << "3) User tests" << endl;
    string userName = "GeorgeM";
    string password = "12345";

    assert(bank->createUser(userName, password));   // Make new user
    assert(bank->userLogin(userName, password));    // Login succesfully
    assert(!bank->createUser(userName, "random"));  // Fail to make same username
    assert(!bank->userLogin(userName, "random"));   // Fail to login


    bank->showAccounts();
    delete bank;
}

void cliTests() {
    return;
}