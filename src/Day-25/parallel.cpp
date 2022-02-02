#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <numeric>

template<typename Iterator, typename T>
struct accumulate_block {
    void operator()(Iterator first, Iterator last, T init, std::promise<T> p) {
        T t = std::accumulate(first, last, init);
        p.set_value(t);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first,last);
    if(!length) return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads:2,max_threads);
    std::cout << "num_threads: " << num_threads << std::endl;
    unsigned long const block_size = length/num_threads;

    std::vector<std::promise<T>> promises(num_threads);
    std::vector<std::future<T>> futures(num_threads);
    for(int i = 0; i < num_threads; i++)
        futures.at(i) = promises.at(i).get_future();
    


    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads);

    Iterator block_start = first;
    for(unsigned long i =0; i < (num_threads -1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator,T>(), block_start, block_end, 0, std::move(promises.at(i)));
        block_start = block_end;
    }
    threads.back() = std::thread(accumulate_block<Iterator,T>(), block_start, last, 0, std::move(promises.back()));

    for(int i = 0; i < futures.size(); i++)
        results.at(i) = futures.at(i).get();
    
    for(auto& entry: threads)
        entry.join();

    return std::accumulate(results.begin(), results.end(), init);
}

int main(void) {
    std::vector<unsigned long> v;
    for(int i = 0; i < 1000; i++)
        v.push_back(i);

    unsigned long result = parallel_accumulate(v.begin(), v.end(), 0);

    std::cout << "result: " << result << std::endl;

    return 0;
}