#include "currency.h"


// Currency

Currency::Currency(void): amount(0.) { }

Currency::Currency(double d): amount(d) { }

double Currency::getAmount(void) const {
    return amount;
}

void Currency::setAmount(double d) {
    amount = d;
}

std::string Currency::printAmount(void) const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << amount;
    return ss.str();
}


// USD

USD::USD(void) { }

USD::USD(double d): Currency(d) { }

std::string USD::printAmount(void) const {
    return (Currency::printAmount() + " USD");
}


// EUR

EUR::EUR(void) {}

EUR::EUR(double d): Currency(d) { }

std::string EUR::printAmount(void) const {
    return (Currency::printAmount() + " EUR");
}


// JPY

JPY::JPY(void) { }

JPY::JPY(double d): Currency(d) { }

std::string JPY::printAmount(void) const { 
    return (Currency::printAmount() + " JPY");
}


// GBP

GBP::GBP(void) { }

GBP::GBP(double d): Currency(d) { }

std::string GBP::printAmount(void) const {
    return (Currency::printAmount() + " GBP");
}