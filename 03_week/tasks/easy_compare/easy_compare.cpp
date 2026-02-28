#include <stdexcept>


struct Date {
    unsigned year = 0;
    unsigned month = 0;
    unsigned day = 0;
};

bool operator==(const Date& a, const Date& b) {
    return std::tie(a.year, a.month, a.day) == std::tie(b.year, b.month, b.day);
}

bool operator<(const Date& a, const Date& b) {
    return std::tie(a.year, a.month, a.day) <  std::tie(b.year, b.month, b.day);
}

bool operator!=(const Date& a, const Date& b) {
    return !(a == b);
}

bool operator<=(const Date& a, const Date& b) {
    return !(b < a);
}

bool operator>(const Date& a, const Date& b) {
    return b < a;
}

bool operator>=(const Date& a, const Date& b) {
    return !(a < b);
}

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

bool operator==(const StudentInfo& a, const StudentInfo& b) {
    return a.mark == b.mark && a.score == b.score;
}

bool operator!=(const StudentInfo& a, const StudentInfo& b) {
    return !(a == b);
}

bool operator<(const StudentInfo& a, const StudentInfo& b) {
    if (a.mark != b.mark)
        return a.mark > b.mark;

    if (a.score != b.score)
        return a.score < b.score;

    if (a.course != b.course)
        return a.course > b.course;

    return a.birth_date < b.birth_date;
}