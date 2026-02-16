#include <cstring>
#include <string>

class StringView {
public:
    using SizeType = std::size_t;
    static constexpr SizeType npos = static_cast<SizeType>(-1); // аналог std::string::npos

    // Конструктор по умолчанию
    StringView() noexcept : data_(nullptr), size_(0) {}

    // Конструктор от std::string (с позицией и длиной подстроки)
    explicit StringView(const std::string& str,
                        SizeType pos = 0,
                        SizeType count = npos) noexcept {
        if (pos >= str.size()) {
            Reset(); // если pos вне строки → пусто
            return;
        }
        data_ = str.data() + pos;
        SizeType max_len = str.size() - pos;
        size_ = (count == npos || count > max_len) ? max_len : count;
    }

    // Конструктор от C-строки (const char*)
    StringView(const char* cstr) noexcept {
        if (!cstr) {
            Reset();
            return;
        }
        data_ = cstr;
        size_ = std::strlen(cstr);
    }

    // Конструктор от C-строки с заданной длиной
    StringView(const char* cstr, SizeType len) noexcept {
        if (!cstr) {
            Reset();
            return;
        }
        data_ = cstr;
        size_ = len;
    }

    // доступ к символам (только чтение)
    const char& operator[](SizeType i) const noexcept { return data_[i]; }

    // указатель на данные
    const char* Data() const noexcept { return data_; }

    // первый и последний символ
    const char& Front() const noexcept { return data_[0]; }
    const char& Back() const noexcept { return data_[size_ - 1]; }

    // размер представления
    SizeType Size() const noexcept { return size_; }
    SizeType Length() const noexcept { return size_; }

    // проверка на пустоту
    bool Empty() const noexcept { return size_ == 0; }

    // убрать n символов с начала
    void RemovePrefix(SizeType n) noexcept {
        if (n >= size_) {
            Reset();
            return;
        }
        data_ += n;
        size_ -= n;
    }

    // убрать n символов с конца
    void RemoveSuffix(SizeType n) noexcept {
        if (n >= size_) {
            Reset();
            return;
        }
        size_ -= n;
    }

    // получить подстроку (новое представление)
    StringView Substr(SizeType pos, SizeType count = npos) const noexcept {
        if (pos >= size_) return StringView();

        SizeType max_len = size_ - pos;
        SizeType len = (count == npos || count > max_len) ? max_len : count;

        return StringView(data_ + pos, len);
    }

    // поиск символа
    SizeType Find(char ch, SizeType pos = 0) const noexcept {
        if (pos >= size_) return npos;

        for (SizeType i = pos; i < size_; ++i) {
            if (data_[i] == ch) return i;
        }
        return npos;
    }

    // поиск подстроки
    SizeType Find(StringView substr, SizeType pos = 0) const noexcept {
        if (substr.size_ == 0) {
            return (pos <= size_) ? pos : npos;
        }
        if (pos > size_ || substr.size_ > size_ - pos) return npos;

        for (SizeType i = pos; i + substr.size_ <= size_; ++i) {
            if (std::memcmp(data_ + i, substr.data_, substr.size_) == 0) {
                return i;
            }
        }
        return npos;
    }

    // преобразование в std::string
    std::string ToString() const {
        return (data_ && size_) ? std::string(data_, size_) : std::string();
    }

private:
    const char* data_; // указатель на начало строки
    SizeType size_;    // длина представления

    // сделать объект пустым
    void Reset() noexcept {
        data_ = nullptr;
        size_ = 0;
    }
};
