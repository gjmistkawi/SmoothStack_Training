#include <iostream>
#include <cassert>
#include <vector>
#include <future>
#include <thread>
#include <numeric>
#include <mutex>

template <typename RandomIt>
void parallel_sum(RandomIt beg, RandomIt end, std::promise<int> p) {
    auto len = end - beg;
    if(len < 1000) {
        p.set_value(std::accumulate(beg, end, 0));
        return;
    }

    RandomIt mid = beg + len/2;
    std::promise<int> p1, p2;
    std::future<int> f1 = p1.get_future();
    std::future<int> f2 = p2.get_future();

    std::thread t1(parallel_sum<RandomIt>, mid, end, std::move(p1));
    std::thread t2(parallel_sum<RandomIt>, beg, mid, std::move(p2));

    p.set_value(f1.get() + f2.get());

    t1.join();
    t2.join();
}



int main(void) {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::vector<int> v(100000, 1);
    std::thread t1(parallel_sum<std::vector<int>::iterator>, v.begin(), v.end(), std::move(p));

    assert(f.get() == 100000);
    t1.join();

    return 0;
}