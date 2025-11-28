#include <cstddef>
#include <stdexcept>
#include <cmath>

double CalculateRMS(double values[], size_t size) {

    // в случае пустовго массива возращаем 0.0
    if (size == 0) {
        return 0.0;
    }

    double sumSq = 0.0;
    // сумма квадратов
    for (size_t i = 0; i < size; ++i) {
        sumSq += values[i] * values[i];
    }
    // RMS
    return std::sqrt(sumSq /size);
}
