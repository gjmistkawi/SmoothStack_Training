#ifndef __currency_h__
#define __currency_h__

#include <typeinfo>
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

#endif
