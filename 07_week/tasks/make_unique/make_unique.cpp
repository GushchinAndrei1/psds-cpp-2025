#include <memory>
#include <utility>

// Создаёт объект типа T в динамической памяти
// и возвращает std::unique_ptr на него.
// Аргументы конструктора передаются через perfect forwarding.
template <typename T, typename... Args>
std::unique_ptr<T> MakeUnique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}