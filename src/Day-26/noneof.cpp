#include <cassert>
#include <atomic>
#include <future>
#include <vector>
#include <iterator>

template<typename Iterator,typename MatchFunc>
bool parallel_none_of_impl(Iterator first, Iterator last, MatchFunc match, std::atomic<bool>& done) {
    try {
        unsigned long const length = std::distance(first, last);
        unsigned long const min_per_thread =25;
        if (length < (2*min_per_thread)) {
            for (;(first != last) && !done.load(); ++first) {
                if (match(*first)) {
                    done = true;
                    return false;
                }
            }
            return true;
        } else {
            Iterator const mid_point = first+(length/2);
            std::future<bool> async_result =
                std::async(&parallel_none_of_impl<Iterator,MatchFunc>,
                           mid_point, last, match,std::ref(done));
            bool const direct_result =
                parallel_none_of_impl(first, mid_point, match, done);
            return (direct_result == true)?
                async_result.get():direct_result;
        }
    }
    catch(...) { done = true; throw; }
}

template<typename Iterator,typename MatchFunc>
bool parallel_none_of(Iterator first, Iterator last, MatchFunc match) {
    std::atomic<bool> done(false);
    return parallel_none_of_impl(first, last, match, done);
}

int main(void) {
    std::vector<int> v(10000, 1);
    auto found = parallel_none_of(v.begin(), v.end(), [](const int i) { return i < 0; });
    assert(found == true);
    
    v.at(100) = -1;
    found = parallel_none_of(v.begin(), v.end(), [](const int i) { return i < 0; });
    assert(found == false);

    v.at(100) = 1;
    v.at(9990) = -1;
    found = parallel_none_of(v.begin(), v.end(), [](const int i) { return i < 0; });
    assert(found == false);

    v.at(9990) = 1;
    v.at(5500) = -1;
    found = parallel_none_of(v.begin(), v.end(), [](const int i) { return i < 0; });
    assert(found == false);

    v.at(5500) = 1;
    found = parallel_none_of(v.begin(), v.end(), [](const int i) { return i < 0; });
    assert(found == true);
}