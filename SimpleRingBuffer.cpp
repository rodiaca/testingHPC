//thread-safe fixed-size ring buffer implementation
#include <vector>
#include <mutex>
#include <cstddef>

class RingBuffer {
public:
    explicit RingBuffer(size_t capacity){
        capacity_ = capacity;
        //inicialize the buffer
        buffer_.resize(capacity);
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    };

    bool push(int value) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (size_ == capacity_) return false;
        buffer_[tail_] = value;
        size_++;
        tail_ = (tail_ + 1) % capacity_;
        mutex_.unlock();

        return true;
    }

    bool pop(int& value){
        std::lock_guard<std::mutex> lock(mutex_);
        if (size_ == 0) return false;
        value = buffer_[head_];
        size_--;
        head_ = (head_ + 1) % capacity_;
        mutex_.unlock();
        return true;
    }

private:
    std::vector<int> buffer_;
    size_t capacity_;
    size_t head_;
    size_t tail_;
    size_t size_;
    std::mutex mutex_;

};

int main() {
    RingBuffer rb(3);

    rb.push(1);
    rb.push(2);
    rb.push(3);

    rb.push(4); // false (full)

    int x;

    rb.pop(x); // x = 1
    rb.pop(x); // x = 2

    rb.push(4);

    rb.pop(x); // x = 3
    rb.pop(x); // x = 4

    return true;
}