#ifndef __currency_h__
#define __currency_h__

#include <typeinfo>
#include <iostream>
#include <iomanip>
#include <sstream>


class Currency {
private:
    double amount;

public:
    Currency(void);
    Currency(double d);

    virtual double getAmount(void) const;
    virtual void setAmount(double d);
    virtual std::string printAmount(void) const;
};

class USD: public Currency {
public:
    USD(void);
    USD(double d);

    std::string printAmount(void) const;
};

class EUR: public Currency {
public:
    EUR(void);
    EUR(double d);

    std::string printAmount(void) const;
};

class JPY: public Currency {
public:
    JPY(void);
    JPY(double d);

    std::string printAmount(void) const;
};

class GBP: public Currency {
public:
    GBP(void);
    GBP(double d);

    std::string printAmount(void) const;
};


class Convert {
private:
    static constexpr double rateUSA = 1.0; //using dollar as base
    static constexpr double rateEUR = 0.88;
    static constexpr double rateJPY = 114.24;
    static constexpr double rateGBP = 0.73;
    
public:
    // T = new, Q = old
    template<typename T, typename Q>
    static T convert(Q q) {
        double oldRate, newRate;

        // old currency type convert
        if(typeid(q) == typeid(USD))
            oldRate = rateUSA;
        else if(typeid(q) == typeid(EUR))
            oldRate = rateEUR;
        else if(typeid(q) == typeid(JPY))
            oldRate = rateJPY;
        else if(typeid(q) == typeid(GBP))
            oldRate = rateGBP;
        else
            throw std::invalid_argument("Invalid Currency - Old");

        // old currency type convert
        if(typeid(T) == typeid(USD))
            newRate = rateUSA;
        else if(typeid(T) == typeid(EUR))
            newRate = rateEUR;
        else if(typeid(T) == typeid(JPY))
            newRate = rateJPY;
        else if(typeid(T) == typeid(GBP))
            newRate = rateGBP;
        else
            throw std::invalid_argument("Invalid Currency - New");

        // convert old amount to base rate, convert that to new rate
        return T((q.getAmount() / oldRate * newRate));
    }
};

#endif
