#ifndef __account_h__
#define __account_h__

#include <iostream>
#include "currency.h"

// T -> type of amt, C -> convert object type
template <typename T, typename C>
class Account {
private:
    T amt;

public:

    // Constructors

    Account(void): amt(nullptr) {}
    Account(T t): amt(t) {}

    Account(const Account& a) {
        amt = a.amt;
    }

    Account(Account&& a) {
        amt = a.amt;
        a.amt = 0;
    }


    // General Functions

    template <typename Q>
    T deposit(Q q) {
        if(std::is_same<Q, T>::value)
            amt.setAmount(amt.getAmount() + q.getAmount());
        
        else
            amt.setAmount(amt.getAmount() + C::template convert<T>(q).getAmount());

        return amt;
    }

    template <typename Q>
    T withdraw(Q q) {
        if(std::is_same<Q, T>::value)
            amt.setAmount(amt.getAmount() - q.getAmount());

        else
            amt.setAmount(amt.getAmount() - C::template convert<T>(q).getAmount());

        return amt;
    }

    template <typename R>
    Account<R, C>* currency() {
        return new Account<R,C>(R(C::template convert<R>(amt)));
    }

    T getBalance() const {
        return amt;
    }


    // Operators - copy/move

    Account& operator=(const Account& a) {
        amt = a.amt;
    }
    
    Account& operator=(Account&& a) {
        if(this == &a) return *this;
        amt = a.amt;
        return *this;
    }


    // Operators - logical

    template <typename Q>
    bool operator==(const Account<Q, C> a) const {
        if(!std::is_same<Q, T>::value)
            return (amt.printAmount() == C::template convert<T>(a.getBalance()).printAmount());
        else
            return (amt.printAmount() == a.getBalance().printAmount());
    }

    template <typename Q>
    bool operator!=(const Account<Q, C> a) const {
        return !(*this == a);
    }

    template <typename Q>
    bool operator<(const Account<Q, C> a) const {
        T t;
        if(!std::is_same<Q, T>::value)
            t = C::template convert<T>(a.getBalance());
            
        return (amt.getAmount() < t.getAmount());
    }

    template <typename Q>
    bool operator>(const Account<Q, C> a) const {
        return !(*this < a || *this == a);
    } 

    template <typename Q>
    bool operator>=(const Account<Q, C> a) const {
        return (*this > a || *this == a);
    } 

    template <typename Q>
    bool operator<=(const Account<Q, C> a) const {
        return (*this < a || *this == a);
    } 


    // Operators - arithmetic

    template <typename X>
    Account<T, C> operator+(const X x) {
        Account<T, C> a(amt.getAmount() + x);
        return a;
    }

    template <typename X>
    Account<T, C> operator-(const X x) {
        Account<T, C> a(amt.getAmount() - x);
        return a;
    }

    template <typename X>
    Account<T, C> operator*(const X x) {
        Account<T, C> a(amt.getAmount() * x);
        return a;
    }

    template <typename X>
    Account<T, C> operator/(const X x) {
        Account<T, C> a(amt.getAmount() / x);
        return a;
    }

    template <typename X>
    Account<T, C>& operator+=(const X x) {
        amt.setAmount(amt.getAmount() + x);
        return *this;
    }

    template <typename X>
    Account<T, C>& operator-=(const X x) {
        amt.setAmount(amt.getAmount() - x);
        return *this;
    }

    template <typename X>
    Account<T, C>& operator*=(const X x) {
        amt.setAmount(amt.getAmount() * x);
        return *this;
    }

    template <typename X>
    Account<T, C>& operator/=(const X x) {
        amt.setAmount(amt.getAmount() / x);
        return *this;
    }

    template <typename X>
    Account<T, C>& operator++(const X x) {
        amt.setAmount(amt.getAmount() + 1);
        return *this;
    }

    template <typename X>
    Account<T, C>& operator--(const X x) {
        amt.setAmount(amt.getAmount() - 1);
        return *this;
    }


    // Operators - cast

    template <typename Q>
    operator Account<Q, C>() {
        return *(this->currency<Q>());
    }
};

#endif