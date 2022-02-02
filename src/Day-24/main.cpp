#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include "safe-queue.cpp"


void push_thread(SafeQueue<int> &sq);
void pop_thread(SafeQueue<int> &sq);

std::mutex print_mut;

int main(void) {
    SafeQueue<int> sq;

    std::thread t1(push_thread, std::ref(sq));
    std::thread t2(pop_thread, std::ref(sq));

    t1.join();
    t2.join();

    return 0;
}

void push_thread(SafeQueue<int> &sq) {
    for(int i = 0; i < 10; i++) {
        sq.push(i);

        print_mut.lock();
        std::cout << "push: " << i << std::endl;
        print_mut.unlock();
    }
}

void pop_thread(SafeQueue<int> &sq) {
    while(!sq.empty()) {
        std::shared_ptr<int> i = sq.try_pop();

        print_mut.lock();
        std::cout << "pop: " << *i << std::endl;
        print_mut.unlock();
    }
}