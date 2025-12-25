#include <stdexcept>
#include <vector>

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

static constexpr uint8_t flags_bits(CheckFlags flags) {
    return static_cast<uint8_t>(flags);
}

static constexpr uint8_t VALID_FLAGS = flags_bits(CheckFlags::ALL);

CheckFlags operator|(CheckFlags left, CheckFlags right) {
    return static_cast<CheckFlags>(
        (flags_bits(left) | flags_bits(right)) & VALID_FLAGS
    );
}

bool operator&(CheckFlags left, CheckFlags right) {
    uint8_t left_flags  = flags_bits(left)  & VALID_FLAGS;
    uint8_t right_flags = flags_bits(right) & VALID_FLAGS;

    return left_flags && right_flags &&
           ((left_flags & right_flags) == left_flags ||
            (left_flags & right_flags) == right_flags);
}

CheckFlags operator^(CheckFlags left, CheckFlags right) {
    return static_cast<CheckFlags>(
        (flags_bits(left) ^ flags_bits(right)) & VALID_FLAGS
    );
}

CheckFlags operator~(CheckFlags flags) {
    return static_cast<CheckFlags>(
        (~flags_bits(flags)) & VALID_FLAGS
    );
}

std::ostream& operator<<(std::ostream& output, CheckFlags flags) {
    uint8_t active_flags = flags_bits(flags) & VALID_FLAGS;

    if (active_flags == 0) {
        output << "NONE";
        return output;
    }

    bool add_separator = false;

    if (active_flags & flags_bits(CheckFlags::TIME)) {
        output << "TIME";
        add_separator = true;
    }

    if (active_flags & flags_bits(CheckFlags::DATE)) {
        if (add_separator) output << ", ";
        output << "DATE";
        add_separator = true;
    }

    if (active_flags & flags_bits(CheckFlags::USER)) {
        if (add_separator) output << ", ";
        output << "USER";
        add_separator = true;
    }

    if (active_flags & flags_bits(CheckFlags::CERT)) {
        if (add_separator) output << ", ";
        output << "CERT";
        add_separator = true;
    }

    if (active_flags & flags_bits(CheckFlags::KEYS)) {
        if (add_separator) output << ", ";
        output << "KEYS";
        add_separator = true;
    }

    if (active_flags & flags_bits(CheckFlags::DEST)) {
        if (add_separator) output << ", ";
        output << "DEST";
    }

    return output;
}