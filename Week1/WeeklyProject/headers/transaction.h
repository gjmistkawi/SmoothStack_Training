#ifndef __transaction_h__
#define __transaction_h__

#include <iostream>
#include <string>
#include <ctime>

using namespace std;


class Transaction {
    public:
        enum Transaction_Type {debit, credit};

        Transaction(void);
        Transaction(long,long,Transaction_Type);

        // Getters
        long    getDollars(void);
        long    getCents(void);
        Transaction_Type getTransactionType(void);

        // Printing methods
        string  printTransaction(void);


    private:
        long _dollars;
        long _cents;
        Transaction::Transaction_Type _type;
};

#endif