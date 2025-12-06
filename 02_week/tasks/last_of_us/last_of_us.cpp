#include <stdexcept>
// для случая (nullptr, nullptr)
int* FindLastElement(std::nullptr_t, std::nullptr_t, bool (*)(int)) {
    return nullptr; 
}
// Функция ищет последний элемент, удовлетворяющий предикату,
// в диапазоне [begin, end). Возвращает указатель на найденный элемент.
// Если элемент не найден или диапазон некорректный, возвращает end.
int* FindLastElement(int* begin, int* end, bool (*predicate)(int)) {
    if (begin == nullptr || end == nullptr || begin > end || predicate == nullptr) {
        return end;
    }

    // Перебираем элементы с конца диапазона
    for (int* i = end - 1; i >= begin; --i) {
        if (predicate(*i)) {
            return i; // сразу возвращаем первый подходящий справа
        }
    }

    // если ничего не нашли, то возвращаем end
    return end;
}

// Перегрузка для const int*.
// Снимаем const, чтобы переиспользовать логику из версии для int*.
const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    return FindLastElement(const_cast<int*>(begin), const_cast<int*>(end), predicate);
}