#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <type_traits>

class USD {
public:
    double amount;

    USD() {}
    USD(double d): amount(d) {}
    static double getExchangeRate() {return 0.74;}
};

class GBP {
public:
    double amount;

    GBP() {}
    GBP(double d): amount(d) {}
    static double getExchangeRate() {return 1.34;}
};

class Country {
private:
    USD usdBalance;
    GBP gbpBalance;

public:
    Country(): usdBalance(USD(1000000.)), gbpBalance(GBP(1000000.)) {}
    std::mutex m;

    template<typename T>
    void requestTradeDeadlock(Country& c, double rate, double amount, T t, bool deposit) {
        // lock both
        const std::lock_guard<std::mutex> l1(m);
        const std::lock_guard<std::mutex> l2(c.m);

        // transaction
        int mult = (deposit ? -1 : 1);  // if deposit, multiplier is negative, else positive

        if(std::is_same<T, USD>::value) {
            usdBalance.amount += amount * mult;
            c.gbpBalance.amount -= amount * rate * mult;
        }

        else {
            gbpBalance.amount += amount * mult;
            c.usdBalance.amount -= amount * rate * mult;
        }
        // automatically unlocks when lock_gaurd goes out of scope unlock both
    }

    template<typename T>
    void requestTrade(Country& c, double rate, double amount, T t, bool deposit) {
        // lock both
        std::scoped_lock lck{m, c.m};

        // transaction
        int mult = (deposit ? -1 : 1);  // if deposit, multiplier is negative, else positive

        if(std::is_same<T, USD>::value) {
            usdBalance.amount += amount * mult;
            c.gbpBalance.amount -= amount * rate * mult;
        }

        else {
            gbpBalance.amount += amount * mult;
            c.usdBalance.amount -= amount * rate * mult;
        }
        // automatically unlocks when lock_gaurd goes out of scope unlock both
    }
};

void test_fixed(Country& c1, Country& c2, std::string name) {
    for(int i = 0; i < 10; i++) {
        c1.requestTrade(c2, USD::getExchangeRate(), 2000., USD(), true);
        c1.requestTrade(c2, GBP::getExchangeRate(), 3000., GBP(), false);
        std::cout << name << ": " << i << std::endl;
    }
}

void test_deadlock(Country& c1, Country& c2, std::string name) {
    for(int i = 0; i < 10; i++) {
        c1.requestTradeDeadlock(c2, USD::getExchangeRate(), 2000., USD(), true);
        c1.requestTradeDeadlock(c2, GBP::getExchangeRate(), 3000., GBP(), false);
        std::cout << name << ": " << i << std::endl;
    }
}


int main(void) {
    Country c1, c2;

    std::thread t1(test_fixed, std::ref(c1), std::ref(c2), "thread 1");
    std::thread t2(test_fixed, std::ref(c2), std::ref(c1), "thread 2");

    //std::thread t1(test_deadlock, std::ref(c1), std::ref(c2), "thread 1");
    //std::thread t2(test_deadlock, std::ref(c2), std::ref(c1), "thread 2");

    t1.join();
    t2.join();

    return 0;
}