#include <initializer_list>
#include <utility>

template <typename T, std::size_t N>
class Array {
public:
    // Конструкторы и деструктор
    Array();
    Array(std::initializer_list<T> init);
    Array(const Array& other);
    Array(Array&& other);
    Array& operator=(const Array& other);
    Array& operator=(Array&& other);
    ~Array();

    // Операторы индексирования []
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    // Возвращает ссылку на первый элемент массива
    T& Front();
    const T& Front() const;

    // Возвращает ссылку на последний элемент массива
    T& Back();
    const T& Back() const;

    // Прямой доступ к памяти
    T* Data();
    const T* Data() const;

    // Возвращает true, если контейнер пуст
    bool Empty() const;

    // Возвращает размер контейнера
    std::size_t Size() const;

    // Заполняет контейнер определенным элементом
    void Fill(const T& value);

    // Обменивается содержимым с другим аналогичным контейнером
    void Swap(Array& other);

    // Поддержка range-based for
    T* begin();
    const T* begin() const;

    T* end();
    const T* end() const;

    // Возвращающие указатель на соответствующий константный элемент
    const T* cbegin() const;
    const T* cend() const;

private:
    // Массив на стеке
    T data_[N == 0 ? 1 : N]{};
};

template <typename T, std::size_t N>
Array<T, N>::Array() = default;

template <typename T, std::size_t N>
Array<T, N>::Array(std::initializer_list<T> init) {
    std::size_t i = 0;
    for (const auto& value : init) {
        if (i >= N) {
            break;
        }
        data_[i] = value;
        ++i;
    }
}

template <typename T, std::size_t N>
Array<T, N>::Array(const Array& other) = default;

template <typename T, std::size_t N>
Array<T, N>::Array(Array&& other) = default;

template <typename T, std::size_t N>
Array<T, N>& Array<T, N>::operator=(const Array& other) = default;

template <typename T, std::size_t N>
Array<T, N>& Array<T, N>::operator=(Array&& other) = default;

template <typename T, std::size_t N>
Array<T, N>::~Array() = default;

template <typename T, std::size_t N>
T& Array<T, N>::operator[](std::size_t index) {
    return data_[index];
}

template <typename T, std::size_t N>
const T& Array<T, N>::operator[](std::size_t index) const {
    return data_[index];
}

template <typename T, std::size_t N>
T& Array<T, N>::Front() {
    return data_[0];
}

template <typename T, std::size_t N>
const T& Array<T, N>::Front() const {
    return data_[0];
}

template <typename T, std::size_t N>
T& Array<T, N>::Back() {
    return data_[N - 1];
}

template <typename T, std::size_t N>
const T& Array<T, N>::Back() const {
    return data_[N - 1];
}

template <typename T, std::size_t N>
T* Array<T, N>::Data() {
    return data_;
}

template <typename T, std::size_t N>
const T* Array<T, N>::Data() const {
    return data_;
}

template <typename T, std::size_t N>
bool Array<T, N>::Empty() const {
    return N == 0;
}

template <typename T, std::size_t N>
std::size_t Array<T, N>::Size() const {
    return N;
}

template <typename T, std::size_t N>
void Array<T, N>::Fill(const T& value) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] = value;
    }
}

template <typename T, std::size_t N>
void Array<T, N>::Swap(Array& other) {
    for (std::size_t i = 0; i < N; ++i) {
        std::swap(data_[i], other.data_[i]);
    }
}

template <typename T, std::size_t N>
T* Array<T, N>::begin() {
    return data_;
}

template <typename T, std::size_t N>
const T* Array<T, N>::begin() const {
    return data_;
}

template <typename T, std::size_t N>
T* Array<T, N>::end() {
    return data_ + N;
}

template <typename T, std::size_t N>
const T* Array<T, N>::end() const {
    return data_ + N;
}

template <typename T, std::size_t N>
const T* Array<T, N>::cbegin() const {
    return data_;
}

template <typename T, std::size_t N>
const T* Array<T, N>::cend() const {
    return data_ + N;
}

// Операторы сравнения
template <typename T, std::size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        if (!(lhs[i] == rhs[i])) {
            return false;
        }
    }
    return true;
}

template <typename T, std::size_t N>
bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs == rhs);
}

// Лексикографическое сравнение
template <typename T, std::size_t N>
bool operator<(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        if (lhs[i] < rhs[i]) {
            return true;
        }
        if (rhs[i] < lhs[i]) {
            return false;
        }
    }
    return false;
}

template <typename T, std::size_t N>
bool operator>(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return rhs < lhs;
}

template <typename T, std::size_t N>
bool operator<=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(rhs < lhs);
}

template <typename T, std::size_t N>
bool operator>=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs < rhs);
}

// Функция swap
template <typename T, std::size_t N>
void swap(Array<T, N>& lhs, Array<T, N>& rhs) {
    lhs.Swap(rhs);
}

// Функция get
template <std::size_t I, typename T, std::size_t N>
T& get(Array<T, N>& array) {
    static_assert(I < N);
    return array[I];
}

template <std::size_t I, typename T, std::size_t N>
const T& get(const Array<T, N>& array) {
    static_assert(I < N);
    return array[I];
}

template <std::size_t I, typename T, std::size_t N>
T&& get(Array<T, N>&& array) {
    static_assert(I < N);
    return std::move(array[I]);
}

template <std::size_t I, typename T, std::size_t N>
const T&& get(const Array<T, N>&& array) {
    static_assert(I < N);
    return std::move(array[I]);
}