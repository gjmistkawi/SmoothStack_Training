#include <mutex>
#include <queue>
#include <memory>

template<typename T>
class SafeQueue {
private:
    std::queue<T> data_queue;
    std::mutex mut;

public:
    SafeQueue() {}

    T back() {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.back();
    }

    T front() {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.front();
    }

    void emplace(T t) {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.emplace(t);
    }

    bool empty() {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }


    int size() {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.size();
    }

    void push(T t) {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(t);
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
};