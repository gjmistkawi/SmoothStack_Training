#include "bignumber.h"

BigNumber::BigNumber(long num) {
    this->set(num);
}

long BigNumber::number() const {
    return _num;
}

void BigNumber::set(long num) {
    _num = num;
}

void BigNumber::multiply(const BigNumber input, BigNumber& output) {
    long result = _num * input.number();
    output.set(result);
}