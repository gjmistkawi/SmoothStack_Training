#include "headers/protoreadwrite.h"

Bank* ProtoReadWrite::readFromDisk() {
    BANK::Bank *storedBank = new BANK::Bank();

    fstream input("bank.data", ios::in | ios::binary);
    if(!input) {
        cout << "bank.data File not found. Creating new file." << endl;
    } else if (!storedBank->ParseFromIstream(&input)) {
        cout << "Failed to parse address book" << endl;
    }


    // Load account data
    map<int,Account*>* allAccounts = new map<int,Account*>();

    for(int i = 0; i < storedBank->allaccounts_size(); i++) {
        BANK::Account accData = storedBank->allaccounts(i);
        vector<Transaction*>* transactions = new vector<Transaction*>();

        for(int j = 0; j < accData.transactions_size(); j++) {
            BANK::Transaction tranData = accData.transactions(j);

            transactions->push_back(new Transaction((long)tranData.dollars(), (long)tranData.cents(), (Transaction::Transaction_Type)tranData.type()));
        }
        
        allAccounts->insert({accData.accountnum(), new Account( accData.accountnum(),
                                                                accData.ssn(),
                                                                accData.firstname(),
                                                                accData.lastname(),
                                                                accData.opendate(),
                                                                (long) accData.dollars(),
                                                                (long) accData.cents(),
                                                                transactions)});
    }


    // Load User data
    map<string,User*>* allUsers = new map<string,User*>();

    for(int i = 0; i < storedBank->allusers_size(); i++) {
        BANK::User userData = storedBank->allusers(i);
        User* user = new User();
        user->loadUser(userData.username(), userData.password());
        allUsers->insert({userData.username(), user});
    }


    // Load error log
    vector<string>* errorLog = new vector<string>();

    for(int i = 0; i < storedBank->errorlog_size(); i++) {
        errorLog->push_back(storedBank->errorlog(i).error());
    }


    Bank* b = new Bank(allAccounts, allUsers, errorLog);
    return b;
}

void ProtoReadWrite::writeToDisk(Bank* b) {
    BANK::Bank* bank = b->saveBankData();

    fstream output("bank.data", ios::out | ios::trunc | ios::binary);
    if(!bank->SerializeToOstream(&output)) {
        cout << "Failed to write bank data" << endl << endl;
    }

    delete bank;
    google::protobuf::ShutdownProtobufLibrary();

}