#ifndef __bignumber_h__
#define __bignumber_h__

class BigNumber {
    private:
        long _num;
    
    public:
        BigNumber(long num);

        long number() const;
        void set(long num);
        void multiply(const BigNumber input, BigNumber& output);
};

#endif