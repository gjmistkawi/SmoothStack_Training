#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

class Sequence {
private:
    std::vector<int> seq;

public:
    std::mutex m;

    Sequence(int n) {
        seq.push_back(n);
    }

    void next() {
        if((seq.back() % 2) == 0)
            seq.push_back(seq.back() / 2);
        else
            seq.push_back((seq.back() * 3) + 1);
    }

    int end() {
        return seq.back();
    }

    void print() {
        std::cout << "[ ";
        for(int i: seq)
            std::cout << i << ", ";
        std::cout << "\b\b ]" << std::endl;
    }
};

void raceCondition(Sequence &s) {
    while(s.end() != 1) {
        s.next();
    }
}

void fixed(Sequence &s) {
    while(s.end() != 1) {
        if(s.m.try_lock()) {
            s.next();
            s.m.unlock();
        }
    }
}

int main(void) {
    // Race Condition Test
    /*
    Sequence s1(13);

    std::thread t1(raceCondition, std::ref(s1));
    std::thread t2(raceCondition, std::ref(s1));

    t1.join();
    t2.join();

    s1.print();
    */


    // Fixed Sequence
    Sequence s2(5);

    std::thread t3(fixed, std::ref(s2));
    std::thread t4(fixed, std::ref(s2));

    t3.join();
    t4.join();

    s2.print();

    return 0;
}