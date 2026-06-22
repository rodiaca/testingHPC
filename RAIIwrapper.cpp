#include <iostream>

class Buffer {
public:
// Constructor
    explicit Buffer(size_t size)
        : size_(size), data_(nullptr)
    {
        if (size_ > 0) {
            data_ = (int*)malloc(size_ * sizeof(int));
        }
    }

    // Destructor
    ~Buffer() {
        free(data_);
    }

    // COPY constructor (deep copy)
    Buffer(const Buffer& other)
        : size_(other.size_), data_(nullptr)
    {
        if (size_ > 0) {
            data_ = (int*)malloc(size_ * sizeof(int));
            memcpy(data_, other.data_, size_ * sizeof(int));
        }
    }

    // COPY assignment
    Buffer& operator=(const Buffer& other) {
        if (this == &other) {
            return *this;
        }

        int* new_data = nullptr;

        if (other.size_ > 0) {
            new_data = (int*)std::malloc(other.size_ * sizeof(int));
            std::memcpy(new_data, other.data_, other.size_ * sizeof(int));
        }

        std::free(data_);

        data_ = new_data;
        size_ = other.size_;

        return *this;
    }

    // MOVE constructor
    Buffer(Buffer&& other) noexcept
        : size_(other.size_), data_(other.data_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    // MOVE assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        std::free(data_);

        data_ = other.data_;
        size_ = other.size_;

        other.data_ = nullptr;
        other.size_ = 0;

        return *this;
    }

private:
    size_t size_;
    int* data_;
};


int main() {
    std::cout << "=== Creating buffer A ===\n";
    Buffer a(5);

    std::cout << "=== Filling buffer A (conceptually) ===\n";
    // assume you have some way to access data (e.g. for testing only)
    // a.data_[i] = i;

    std::cout << "=== Copy constructor: Buffer b = a ===\n";
    Buffer b = a;

    std::cout << "=== Move constructor: Buffer c = std::move(a) ===\n";
    Buffer c = std::move(a);

    std::cout << "=== Copy assignment: d = b ===\n";
    Buffer d(3);
    d = b;

    std::cout << "=== Move assignment: d = std::move(c) ===\n";
    d = std::move(c);

    std::cout << "=== Self-assignment test ===\n";
    d = std::move(d);

    std::cout << "=== End of scope (destructors will run) ===\n";

    return 0;
}
