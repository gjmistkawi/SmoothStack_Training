#include <cassert>
#include <future>
#include <algorithm>
#include <vector>
#include <iterator>

struct join_threads { 
    std::vector<std::thread>& myvec;
    join_threads(std::vector<std::thread>& vec) : myvec(vec) {}
    ~join_threads() {
        for (auto& ele : myvec) {
            ele.join();
        }
    }
};

template<typename Iterator, typename MatchFunc>
bool parallel_any_of(Iterator first, Iterator last, MatchFunc match) {
    struct find_match {
        void operator()(Iterator begin, Iterator end, MatchFunc match,
                        std::promise<bool>* result,
                        std::atomic<bool>* done_flag) {
            try {
                for(;(begin != end) && !done_flag->load(); ++begin) {
                    if (match(*begin)) {
                        result->set_value(true);
                        done_flag->store(true);
                        return;
                    }
                }
            } catch(...) {
                try {
                    result->set_exception(std::current_exception());
                    done_flag->store(true);
                } catch(...) {}
            }
        }
    };

    unsigned long const length = std::distance(first, last);

    if(!length)
        return false;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;

    unsigned long const hardware_threads = std::thread::hardware_concurrency();

    unsigned long const num_threads = std::min(hardware_threads!=0?hardware_threads:2,max_threads);

    unsigned long const block_size = length/num_threads;

    std::promise<bool> result;
    std::atomic<bool> done_flag(false);
    std::vector<std::thread> threads(num_threads-1);

    //critical section
    {
        join_threads joiner(threads);

        Iterator block_start=first;
        for (unsigned long i=0; i < (num_threads-1); ++i) {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);
            threads[i] = std::thread(find_match(), block_start, block_end, match, &result, &done_flag);
            block_start = block_end;
        }
        find_match()(block_start,last, match, &result, &done_flag);
    }

    if(!done_flag.load()) { //if a match is still not found
        return false;
    }
    return result.get_future().get();
}


int main(void) {
    std::vector<int> v(10000, 1);
    auto found = parallel_any_of(v.begin(), v.end(), [](const int i) { return i < 0; });
    assert(found == false);
    
    v.at(100) = -1;
    found = parallel_any_of(v.begin(), v.end(), [](const int i) { return i < 0; });
    assert(found == true);

    v.at(100) = 1;
    v.at(9990) = -1;
    found = parallel_any_of(v.begin(), v.end(), [](const int i) { return i < 0; });
    assert(found == true);

    v.at(9990) = 1;
    v.at(5500) = -1;
    found = parallel_any_of(v.begin(), v.end(), [](const int i) { return i < 0; });
    assert(found == true);

    v.at(5500) = 1;
    found = parallel_any_of(v.begin(), v.end(), [](const int i) { return i < 0; });
    assert(found == false);
}