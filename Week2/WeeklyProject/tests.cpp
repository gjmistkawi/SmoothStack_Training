#include <iostream>
#include <cassert>
#include "headers/account.h"
#include "headers/user.h"
#include "headers/bank.h"
#include "headers/transaction.h"
#include "headers/protoreadwrite.h"

using namespace std;

void transactionTests();
void userTests();
void accountTests();
void bankTests();
//void cliTests();
void protobufTests();

int main() {
    cout << "=============================" << endl << endl;
    transactionTests();
    cout << endl << "=============================" << endl << endl;
    userTests();
    cout << endl << "=============================" << endl << endl;
    accountTests();
    cout << endl << "=============================" << endl << endl;
    bankTests();
    //cout << endl << "=============================" << endl << endl;
    //cliTests();
    cout << endl << "=============================" << endl << endl;
    protobufTests();
    cout << endl;

    return 0;
}

//=================================================
//==================== TESTS ======================
//=================================================

void transactionTests() {
    cout << "Transaction Class Unit Testing" << endl << endl;
    long dollars = 100;
    long cents = 99;
    Transaction::Transaction_Type type = Transaction::Transaction_Type::credit;

    Transaction t = Transaction(dollars, cents, type);

    cout << "1) Object creation tests --- ";
    assert(t.getCents() == cents);
    assert(t.getDollars() == dollars);
    assert(t.getTransactionType() == type);
    cout << " PASS" << endl;

    cout << "2) Credit printing tests --- ";
    string message = "+ $" + to_string(dollars) + "." + to_string(cents);
    assert(t.printTransaction() == message);
    cout << " PASS" << endl;

    dollars = 5;
    cents = 9;
    type = Transaction::Transaction_Type::debit;
    t = Transaction(dollars, cents, type);

    cout << "3) Debit printing tests --- ";
    message = "- $" + to_string(dollars) + ".0" + to_string(cents);
    assert(t.printTransaction() == message);
    cout << " PASS" << endl;
}

void userTests() {
    cout << "User Class Unit Testing" << endl << endl;

    string name = "Bobbert93";
    string password = "somerandompass";

    User user = User(name, password);

    cout << "1) Getter tests --- ";
    assert(name == user.getUserName());
    cout << " PASS" << endl;

    cout << "2) Login tests --- ";
    assert(user.login(password));
    assert(!user.login("wrongpassword"));
    cout << " PASS" << endl;
}


void accountTests() {
    cout << "Account Class Unit Testing" << endl << endl;

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

    cout << "1) Getter tests --- ";
    assert(fName == acc1.getFirstName());
    assert(lName == acc1.getLastName());
    assert(ssn == acc1.getSSN());
    assert("$0.00" == acc1.getBalance());
    cout << " PASS" << endl;

    cout << "2) Transaction tests --- ";
    Transaction* t1 = new Transaction(1000, 3, Transaction::Transaction_Type::credit);
    Transaction* t2 = new Transaction(2000, 3, Transaction::Transaction_Type::debit);
    Transaction* t3 = new Transaction(100, 90, Transaction::Transaction_Type::debit);

    assert(acc1.confirmTransaction(t1) == true);
    assert(acc1.getBalance() == "$1000.03");
    assert(acc1.confirmTransaction(t2) == false);
    assert(acc1.getBalance() == "$1000.03");
    delete t2;
    assert(acc1.confirmTransaction(t3) == true);
    assert(acc1.getBalance() == "$899.13");

    vector<Transaction*>* transactions = acc1.getTransactions();
    assert(transactions->at(0) == t1);
    assert(transactions->at(1) == t3);
    cout << " PASS" << endl;

    cout << "3) Display tests --- ";
    string display = "Customer Name: " + fName + " " + lName + "\n"
                    + "SSN: ***-**-" + ssn.substr(ssn.size() - 4) + "\n"
                    + "Date Opened: " + date + "\n"
                    + "Account: " + to_string(accNum) + "\n"
                    + "Balance: " + "$899.13\n";

    string show = fName + " " + lName + ", " 
                    + to_string(accNum) + ", "
                    + date;

    assert(display == acc1.displayAccount());
    assert(show == acc1.showAccount());
    cout << " PASS" << endl;
}


void bankTests() {
    cout << "Bank Class Unit Testing" << endl << endl;
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


    cout << "1) Account creation tests --- ";
    accountNum1 = bank->createAccount(ssn1, fName1, lName1);
    assert(accountNum1 > 0);    // No error messages on creation
    accountNum2 = bank->createAccount(ssn1, fName1, lName1);
    assert(accountNum2 == ERROR_ACCOUNT_EXISTS); // SSN already in use
    accountNum2 = bank->createAccount(ssn2, fName2, lName2);
    assert(accountNum2 > 0);    // No error messages on creation
    assert(accountNum2 != accountNum1); // Accounts have different accountNum
    accountNum3 = bank->createAccount(ssn3, fName3, lName3);
    assert(!bank->displayAccount(accountNum3).empty());
    cout << " PASS" << endl;

    cout << "2) Account display tests --- ";
    assert(bank->showAccounts().size() == 3); // Correct number of accounts displayed

    string display = "Customer Name: " + fName2 + " " + lName2 + "\n"
                    + "SSN: ***-**-" + ssn2.substr(ssn2.size() - 4) + "\n"
                    + "Date Opened: " + date + "\n"
                    + "Account: " + to_string(accountNum2) + "\n"
                    + "Balance: $0.00\n";   
    assert(display == bank->displayAccount(accountNum2));
    cout << " PASS" << endl;

    cout << "3) User creation tests --- ";
    string userName = "GeorgeM";
    string password = "12345";

    assert(bank->createUser(userName, password));   // Make new user
    assert(!bank->createUser(userName, "random"));  // Fail to make same username
    cout << " PASS" << endl;

    cout << "4) User login tests --- ";
    assert(bank->userLogin(userName, password));    // Login succesfully
    assert(!bank->userLogin(userName, "random"));   // Fail to login
    cout << " PASS" << endl;


    //bank->showAccounts();
    delete bank;
}


//void cliTests() {}


void protobufTests() {
    cout << "Protobuf Class Unit Testing" << endl << endl;

    cout << "1) Persistance tests --- ";
    Bank* b = ProtoReadWrite::readFromDisk();

    string fName = "Jeremy";
    string lName = "Fox";
    string ssn = "191919191";

    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(ltm->tm_mon + 1) + "/"
                + to_string(ltm->tm_mday) + "/"
                + to_string(ltm->tm_year + 1900);

    int accountNum = b->createAccount(ssn, fName, lName);

    long dollars = 10;
    long cents = 1;
    Transaction::Transaction_Type type = Transaction::Transaction_Type::credit;
    Transaction* t = new Transaction(dollars, cents, type);
    assert(b->addTransaction(accountNum, t) == true);

    string details = "Customer Name: " + fName + " " + lName + "\n"
                    + "SSN: ***-**-" + ssn.substr(ssn.size() - 4) + "\n"
                    + "Date Opened: " + date + "\n"
                    + "Account: " + to_string(accountNum) + "\n"
                    + "Balance: $" + to_string(dollars) + ".0" + to_string(cents) + "\n";  
    assert(details == b->displayAccount(accountNum));

    ProtoReadWrite::writeToDisk(b);
    delete b;

    b = ProtoReadWrite::readFromDisk();
    assert(details ==  b->displayAccount(accountNum));
    cout << " PASS" << endl;
}