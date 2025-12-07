#include <cstddef>

// Функция ищет самую длинную подпоследовательность одинаковых символов
// в диапазоне [begin, end). Длину подпоследовательности записывает в count.
// Возвращает указатель на начало найденной подпоследовательности.
// В случае ошибки возвращает nullptr. В count записывает 0.
char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    // проверка корректнсти
    if (begin == nullptr || end == nullptr || begin >= end) {
        count = 0;
        return nullptr;
    }

    char* best_start = begin; // начало лучшей подпоследовательности
    size_t best_length = 1; // длина лучшей последовательности

    char* curr_start = begin; // начало текущей последовательности
    size_t curr_length = 1; // длина текущей последовательности

    // Перебираем символы, начиная со второго
    for (char* i = begin + 1; i < end; ++i) {
        // тут проверка на совпадения
        // если совпадает, то увеличивам длину текущей подпоследовательности curr_length
        if (*i == *(i - 1)) {
            ++curr_length;
        } else {
            // Если текущая последовательность строго длиннее лучшей, то
            // обновляем результат. При равных длинах не обновляем, так как
            // по условию возвращается первая
            if (curr_length > best_length) {
                best_start = curr_start;
                best_length = curr_length;
            }
            curr_start = i; // начинаем новую подпоследовательность с текущего символа
            curr_length = 1; // начало новой подпоследовательность
         }
    }
    // Проверяем последнюю подпоследовательность (она могла закончится концом строки)
    if (curr_length > best_length) {
        best_length = curr_length;
        best_start = curr_start;
    }
    // записываем в count лучшую длину
    count = best_length;
    return best_start;
}


// Перегрузка для const char*.
// Код поиска наибольшей подпоследовтаельности уже реализован в версии для char*,
// поэтому здесь будем использовать его,
// временно снимаем const, чтобы вызвать существующую логику
const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    char* result = FindLongestSubsequence(const_cast<char*>(begin),  const_cast<char*>(end), count);
    return result;
}

