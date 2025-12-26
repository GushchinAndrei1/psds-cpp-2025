#include <vector>
#include <stack>
#include <algorithm>

class Queue {
public:
    Queue() = default;

    explicit Queue(size_t capacity) {
        in_.reserve(capacity);
    }

    explicit Queue(const std::vector<int>& vec) {
        in_ = vec;
    }

    explicit Queue(const std::stack<int>& st) {
        std::stack<int> tmp = st;
        std::vector<int> rev;
        rev.reserve(tmp.size());
        while (!tmp.empty()) {
            rev.push_back(tmp.top());
            tmp.pop();
        }
        std::reverse(rev.begin(), rev.end());
        in_ = std::move(rev);
    }

    Queue(std::initializer_list<int> init) {
        in_.assign(init.begin(), init.end());
    }

    void Push(int value) {
        in_.push_back(value);
    }

    bool Pop() {
        if (Empty()) {
            return false;
        }
        EnsureOutNotEmpty();
        out_.pop_back();
        return true;
    }

    int& Front() {
        EnsureOutNotEmpty();
        return out_.back();
    }

    const int& Front() const {
        EnsureOutNotEmpty();
        return out_.back();
    }

    int& Back() {
        if (!in_.empty()) {
            return in_.back();
        }
        return out_.front();
    }

    const int& Back() const {
        if (!in_.empty()) {
            return in_.back();
        }
        return out_.front();
    }

    bool Empty() const {
        return in_.empty() && out_.empty();
    }

    size_t Size() const {
        return in_.size() + out_.size();
    }

    void Clear() {
        in_.clear();
        out_.clear();
    }

    void Swap(Queue& other) {
        if (this == &other) return;
        in_.swap(other.in_);
        out_.swap(other.out_);
    }

    friend bool operator==(const Queue& a, const Queue& b) {
        if (a.Size() != b.Size()) {
            return false;
        }
        return a.ToVector() == b.ToVector();
    }

    friend bool operator!=(const Queue& a, const Queue& b) {
        return !(a == b);
    }

private:
    mutable std::vector<int> in_;
    mutable std::vector<int> out_;

    void EnsureOutNotEmpty() const {
        if (!out_.empty()) {
            return;
        }
        while (!in_.empty()) {
            out_.push_back(in_.back());
            in_.pop_back();
        }
    }

    std::vector<int> ToVector() const {
        std::vector<int> result;
        result.reserve(Size());
        for (auto it = out_.rbegin(); it != out_.rend(); ++it) {
            result.push_back(*it);
        }
        for (int x : in_) {
            result.push_back(x);
        }
        return result;
    }
};
