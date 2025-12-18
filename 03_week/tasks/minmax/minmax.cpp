#include <stdexcept>
#include <vector>

std::pair<std::vector<int>::const_iterator,
          std::vector<int>::const_iterator>
MinMax(const std::vector<int>& v) {
    if (v.empty()) {
        return {v.end(), v.end()};
    }

    auto min_it = v.begin();   // итератор минимума
    auto max_it = v.begin();   // итератор максимума
    bool all_eq = true;
    int first = *v.begin();

    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it != first) {
            all_eq = false;
        }

        if (*it < *min_it) {
            min_it = it;       // первое вхождение минимума
        }

        if (*it >= *max_it) {
            max_it = it;       // последнее вхождение максимума
        }
    }

    if (all_eq) {
        return {v.end() - 1, v.begin()};
    }

    return {min_it, max_it};
}