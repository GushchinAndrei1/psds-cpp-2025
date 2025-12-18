#include <stdexcept>
#include <vector>
#include <cmath>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int>& data) {
    if (data.empty()) {
        return DataStats{};
    }

    double mean = 0.0;
    double M2   = 0.0;
    std::size_t n = 0;

    for (int x : data) {
        ++n;
        double delta = x - mean;
        mean += delta / n;
        double delta2 = x - mean;
        M2 += delta * delta2;
    }

    DataStats result;
    result.avg = mean;
    result.sd  = std::sqrt(M2 / n);

    return result;
}