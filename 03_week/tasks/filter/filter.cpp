#include <stdexcept>
#include <vector>

void Filter(std::vector<int>& data, bool (*pred)(int)) {
    if (!pred) {
        return;
    }

    std::size_t write = 0;

    for (std::size_t read = 0; read < data.size(); ++read) {
        if (pred(data[read])) {
            data[write] = data[read];
            ++write;
        }
    }

    data.resize(write);
}