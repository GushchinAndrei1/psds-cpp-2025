#include <vector>
#include <cstddef>

class RingBuffer {
public:
    explicit RingBuffer(size_t capacity)
        : data_(capacity == 0 ? 1 : capacity), head_(0), size_(0) {}

    RingBuffer(size_t capacity, int value)
        : data_(capacity == 0 ? 1 : capacity, value),
          head_(0),
          size_(capacity == 0 ? 1 : capacity) {}

    RingBuffer(std::initializer_list<int> init)
        : data_(init), head_(0), size_(init.size()) {
        if (data_.empty()) {
            data_.resize(1);
            size_ = 0;
        }
    }

    void Push(int value) {
        if (Full()) {
            data_[head_] = value;
            head_ = (head_ + 1) % data_.size();
        } else {
            data_[Index(size_)] = value;
            ++size_;
        }
    }

    bool TryPush(int value) {
        if (Full()) {
            return false;
        }
        Push(value);
        return true;
    }

    void Pop() {
        if (Empty()) {
            return;
        }
        head_ = (head_ + 1) % data_.size();
        --size_;
    }

    bool TryPop(int& value) {
        if (Empty()) {
            return false;
        }
        value = data_[head_];
        Pop();
        return true;
    }

    int& operator[](size_t index) {
        return data_[Index(index)];
    }

    const int& operator[](size_t index) const {
        return data_[Index(index)];
    }

    int& Front() {
        return data_[Index(size_ - 1)];
    }

    int& Back() {
        return data_[head_];
    }

    bool Empty() const {
        return size_ == 0;
    }

    bool Full() const {
        return size_ == data_.size();
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return data_.size();
    }

    void Clear() {
        head_ = 0;
        size_ = 0;
    }

    void Resize(size_t new_capacity) {
        if (new_capacity == 0) {
            new_capacity = 1;
        }

        std::vector<int> new_data;
        new_data.reserve(new_capacity);

        size_t new_size = size_ < new_capacity ? size_ : new_capacity;

        for (size_t i = size_ - new_size; i < size_; ++i) {
            new_data.push_back((*this)[i]);
        }

        data_ = std::move(new_data);
        data_.resize(new_capacity);

        head_ = 0;
        size_ = new_size;
    }

    std::vector<int> Vector() const {
        std::vector<int> result;
        result.reserve(size_);

        for (size_t i = 0; i < size_; ++i) {
            result.push_back((*this)[i]);
        }
        return result;
    }

private:
    std::vector<int> data_;
    size_t head_;
    size_t size_;

    size_t Index(size_t logical_index) const {
        return (head_ + logical_index) % data_.size();
    }
};
