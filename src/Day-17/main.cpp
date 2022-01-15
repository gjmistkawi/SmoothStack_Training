#include <cassert>
#include <iostream>
#include "currency.h"
#include "account.h"


using std::cout;

//void oldTest(void);

int main(void) {
    GBP g1(500);
    GBP g2(10.50);
    USD* u1 = new USD(5.5);
    JPY j1(50000);

    Account<GBP, Convert> acc1(g1);
    Account<JPY, Convert>* acc2 = acc1.currency<JPY>();

    assert(acc1.getBalance().printAmount() == "500.00 GBP");
    assert(acc2->getBalance().printAmount() == "78246.58 JPY");

    assert(acc1.withdraw(GBP(250.)).printAmount() == "250.00 GBP");
    assert(acc2->deposit(acc1.getBalance()).printAmount() == "117369.86 JPY");

    assert((acc1 + 5).getBalance().printAmount() == "255.00 GBP");
    assert((static_cast<Account<USD, Convert>>(*acc2).getBalance().printAmount()) == "1027.40 USD");

    acc1 -= 5.0;
    assert(acc1.getBalance().printAmount() == "245.00 GBP");
    assert((acc1++).getBalance().printAmount() == "246.00 GBP");

    assert(acc1 == acc1);
    assert(*acc2 != acc1);
    assert(acc1 < *acc2);
    assert(!(acc1 > *acc2));
    assert(*acc2 == *acc2);

    return 0;
}

/*
void oldTest(void) {
    acc1 = acc1 + 5;
    cout << "Acc1 balance: " << acc1.getBalance().printAmount() << std::endl;
    acc1 = acc1 - 331.3;
    cout << "Acc1 balance: " << acc1.getBalance().printAmount() << std::endl;
    acc1 += 331;
    cout << "Acc1 balance: " << acc1.getBalance().printAmount() << std::endl;
    acc1 -= 231.3;
    cout << "Acc1 balance: " << acc1.getBalance().printAmount() << std::endl;
    acc1 *= 5;
    cout << "Acc1 balance: " << acc1.getBalance().printAmount() << std::endl;
    acc1 /= 30;
    cout << "Acc1 balance: " << acc1.getBalance().printAmount() << std::endl;
    acc1 -= acc1.getBalance().getAmount();
    cout << "Acc1 balance: " << acc1.getBalance().printAmount() << std::endl;
    acc1++;
    cout << "Acc1 balance: " << acc1.getBalance().printAmount() << std::endl;
    acc1--;
    cout << "Acc1 balance: " << acc1.getBalance().printAmount() << std::endl;
    cout << "Casting from JPY to USD" << std::endl;
    cout << "Acc2 balance: " << acc2->getBalance().printAmount() << std::endl;
    cout << "Acc2 balance: " << acc2->deposit(j1).printAmount() << std::endl;
    cout << "Acc2 balance: " << static_cast<Account<USD, Convert>>(*acc2).getBalance().printAmount() << std::endl;
    cout << "Acc2 balance: " << static_cast<Account<GBP, Convert>>(*acc2).getBalance().printAmount() << std::endl;

    cout << (acc1 == acc1) << std::endl;
    cout << (acc1 == *acc2) << std::endl;
    cout << (acc1 == static_cast<Account<GBP, Convert>>(*acc2)) << std::endl;
    cout << (acc1 != acc1) << std::endl;
    cout << (acc1 != *acc2) << std::endl;

    cout << ((acc1 < acc1)? "true" : "false") << std::endl;
    cout << acc1.getBalance().printAmount() << " < " << acc2->getBalance().printAmount() << ((acc1 < *acc2)? " true" : " false") << std::endl;
    cout << ((acc1 > acc1)? "true" : "false") << std::endl;
    cout << acc1.getBalance().printAmount() << " > " << acc2->getBalance().printAmount() << ((acc1 > *acc2)? " true" : " false") << std::endl;
    cout << ((acc1 <= acc1)? "true" : "false") << std::endl;
    cout << acc1.getBalance().printAmount() << " <= " << acc2->getBalance().printAmount() << ((acc1 <= *acc2)? " true" : " false") << std::endl;
    cout << ((acc1 >= acc1)? "true" : "false") << std::endl;
    cout << acc1.getBalance().printAmount() << " >= " << acc2->getBalance().printAmount() << ((acc1 >= *acc2)? " true" : " false") << std::endl;
}
*/