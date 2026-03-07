#include <string>
#include <utility>

class UniquePtr {
private:
    std::string* ptr_;

public:

    // Конструктор по умолчанию
    UniquePtr() : ptr_(nullptr) {}

    // Конструктор от сырого указателя
    explicit UniquePtr(std::string* ptr) : ptr_(ptr) {}

    // Удаляем копирование 
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Конструктор перемещения
    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    // Оператор перемещения
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    // Деструктор
    ~UniquePtr() {
        delete ptr_;
    }

    // Операторы указателя
    std::string& operator*() const {
        return *ptr_;
    }

    std::string* operator->() const {
        return ptr_;
    }

    // Получить сырой указатель
    std::string* Get() const {
        return ptr_;
    }

    // Освободить владение
    std::string* Release() {
        std::string* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    // Сбросить указатель
    void Reset(std::string* ptr = nullptr) {
        delete ptr_;
        ptr_ = ptr;
    }

    // Обмен указателями
    void Swap(UniquePtr& other) {
        std::swap(ptr_, other.ptr_);
    }

    // bool преобразование
    explicit operator bool() const {
        return ptr_ != nullptr;
    }
};

template<typename T>
UniquePtr MakeUnique(T&& value) {
    return UniquePtr(new std::string(std::forward<T>(value)));
}

void Swap(UniquePtr& a, UniquePtr& b) {
    a.Swap(b);
}