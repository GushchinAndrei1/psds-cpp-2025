    #include <cstdint>
    #include <stdexcept>

 // каждый флаг это один бит в маске, флаг занимает ровно один
    enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};
    void PrintCheckFlags(CheckFlags flags) {
    // мы не можем напрямую работать с flags, поэтому преобразуем
    // flags из типа CheckFlags в обычное число типа uint8_t
    // uint8_t потому что все флаги храняться в одном байте 
    uint8_t mask = static_cast<uint8_t>(flags);
    // так как маска = 8 бит, то и все разрешенные флаги тоже 8 бит (поэтому uint8_t)
    // но в целом как для mask, так и для allowedFlags могли написать int и не париться, но с uint8_t корректнее
    uint8_t allowedFlags = static_cast<uint8_t>(CheckFlags::ALL);

    // Если передано значение выходит из возможного диапазона значений, то вывод следует оставить пустым.
    //  к примеру если мы на вход подаем значение 128, а 128 в двочиной это 10000000 (mask), allowedFlags = 01111111, то
    //      10000000
    //      11000000 (инверсия)
    //      --------
    //      10000000 (такого флага в маске нет)
    if (mask & ~allowedFlags) {
        return;
    }

    // Если передан флаг отсутствия проверок, то выводим пустые `[]` 
    if (mask == 0) {
        std::cout << "[]";
        return;
    }

    // дальше расматриваем все возможные случаи проверок 
    std::cout << "[";
    // флаг состояний для запятой
    bool first = true;

    if (mask & static_cast<uint8_t>(CheckFlags::TIME)) {
        if (!first) {
            std::cout << ",";
        }
        std::cout << "TIME";
        first = false;
    }

    if (mask & static_cast<uint8_t>(CheckFlags::DATE)) {
        if (!first) {
            std::cout << ",";
        }
        std::cout << "DATE";
        first = false;
    }

    if (mask & static_cast<uint8_t>(CheckFlags::USER)) {
        if (!first) {
            std::cout << ",";
        }
        std::cout << "USER";
        first = false;
    }

    if (mask & static_cast<uint8_t>(CheckFlags::CERT)) {
        if (!first) {
            std::cout << ",";
        }
        std::cout << "CERT";
        first = false;
    }

    if (mask & static_cast<uint8_t>(CheckFlags::KEYS)) {
        if (!first) {
            std::cout << ",";
        }
        std::cout << "KEYS";
        first = false;
    }

    if (mask & static_cast<uint8_t>(CheckFlags::DEST)) {
        if (!first) {
            std::cout << ",";
        }
        std::cout << "DEST";
    }

    std::cout << "]";
}
