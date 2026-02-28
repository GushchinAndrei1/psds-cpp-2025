#include <stdexcept>
#include <cstddef>

std::vector<size_t> FindAll(const std::vector<int>& vec, bool (*predicate)(int))
{
    std::vector<size_t> result;

    if (predicate == nullptr) {
        return result;
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        if (predicate(vec[i])) {
            result.push_back(i);
        }
    }

    result.shrink_to_fit();

    return result;
}
