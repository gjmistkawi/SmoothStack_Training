#include <iostream>

template<typename T>
class myvector {
private:
    T* mData;       // this is the actual data (or array)
    int mSize;      // Size is how much data.  Capacity is how much memory.
    int mCapacity;  // not always same as mSize, usually much larger than mSize.
    T mUndefined;   // Lots of STL functions say that doing something naughty gets "undefined behavior".


public:
    // Constructors
    myvector(): mData(nullptr), mSize(0), mCapacity(0) { }

    myvector(T*, int sz) {
        mData = new T[sz];
        mSize = sz;
        mCapacity = sz;
    }

    // Destructor
    virtual ~myvector() {
        delete mData;
    }

    // Copy Constructor
    myvector(const myvector<T>& other) {
        mData = new T[other.mSize];
        mSize = other.mSize;
        mCapacity = other.mCapacity;

        for(int i = 0; i < mSize; i++) {
            mData[i] = other.mData[i];
        }
    }

    // Move Constructor
    myvector(myvector<T>&& other) {
        mData = other.mData;
        mSize = other.mSize;
        mCapacity = other.mCapacity;

        other.mData = nullptr;
        other.mSize = 0;
        other.mCapacity = 0;
    }

    // Copy Operator
    myvector& operator=(const myvector<T>& other) {
        mData = new T[other.mSize];
        mSize = other.mSize;
        mCapacity = other.mCapacity;

        for(int i = 0; i < mSize; i++) {
            mData[i] = other.mData[i];
        }

        return *this;
    }

    // Comperator Operator
    bool operator==(const myvector<T>& other) {
        if(this == &other) return true;

        bool equiv = true;
        if(mSize == other.mSize) {
            for(int i = 0; i < mSize; i++)
                if(mData[i] != other.mData[i])
                    equiv = false;
        }

        return equiv;
    }

    // Element Access Operator
    T& operator[](int offset) {
        if(offset < 0 || offset > mSize) 
            throw std::out_of_range("out of bounds");

        return mData[offset];
    }


        // Functions
        void push_back(const T& t) {
            if(mCapacity > mSize) {
                mData[mSize] = t;
                mSize++;
            }

            else {
                T* arr = new T[mSize +1];

                for(int i = 0; i < mSize; i++)
                    arr[i] = mData[i];
                arr[mSize] = t;
                
                delete mData;

                mData = arr;
                mSize++;
                mCapacity++;
            }
        }

        void pop_back() {
            if(mSize > 0) mSize--;
        }

        T& at(int offset) {
            if(offset < 0 || offset > mSize) 
                throw std::out_of_range("out of bounds");

            return mData[offset];
        }

        void clear() {
            delete mData;
            mData = nullptr;
            mSize = 0;
            mCapacity = 0;
        }

        void reserve(int tCount) {
            if(mSize >= tCount) return;

            T* arr = new T[tCount];
            for(int i = 0; i < mSize; i++)
                arr[i] = mData[i];

            delete mData;
            mData = arr;
            mCapacity = tCount;
        }

        int size() const {return mSize;}
        int capacity() const {return mCapacity;}




    // iterator
    class iterator {
        friend myvector;
        myvector* _myvec;
        int _current; // offset 
    public:
        iterator(): _myvec(nullptr), _current(0) {}
        iterator(myvector* myvec, int offset): _myvec(myvec), _current(offset) {}
        void operator ++(int) {_current++;}
        void operator --() {_current--;}
        bool operator ==(const iterator& i) {return (_myvec == i._myvec && _current == i._current);}
        bool operator !=(const iterator& i) {return !(*this == i);}
        T& operator*() {return _myvec->at(_current);}
    };


    iterator begin() {return iterator(this, 0);};
    iterator end() {return iterator(this, mSize-1);};
};