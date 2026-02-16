#include <cstddef>
#include <cstring>
#include <string>

class CowString {
public:
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

    // Конструктор по умолчанию
    CowString();
    // Конструктор от const char*
    CowString(const char* cstr);
    // Конструктор от std::string
    CowString(const std::string& s);

    // Конструктор копирования
    CowString(const CowString& other);
    // Присваивание копированием
    CowString& operator=(const CowString& other);

    // Конструктор перемещения
    CowString(CowString&& other) noexcept;
    // Присваивание перемещением
    CowString& operator=(CowString&& other) noexcept;

    // Деструктор
    ~CowString();

    std::size_t Size() const;
    bool Empty() const;

    const char* ToCstr() const;
    std::string ToString() const;

    // [] чтение
    const char& operator[](std::size_t i) const;
    // [] запись
    char& operator[](std::size_t i);

    // Преобразование к C-строке
    operator const char*() const;

    CowString& Append(const char* tail);
    CowString& Append(const std::string& tail);

    CowString Substr(std::size_t pos = 0, std::size_t count = npos) const;

    void Clear();

    std::size_t Find(const char* needle) const;
    std::size_t Find(const std::string& needle) const;
    std::size_t Find(char ch) const;

private:
    struct Buffer {
        char* data;
        std::size_t size;
        std::size_t ref_count;

        Buffer(const char* src, std::size_t len);
        ~Buffer();
    };

    Buffer* buf_;

    void Detach();
    void Release();
};

//Buffer

CowString::Buffer::Buffer(const char* src, std::size_t len)
    : data(new char[len + 1]), size(len), ref_count(1) {
    if (len) std::memcpy(data, src, len);
    data[len] = '\0';
}

CowString::Buffer::~Buffer() {
    delete[] data;
}

//Внутренние методы

void CowString::Release() {
    if (!buf_) return;
    if (--buf_->ref_count == 0) delete buf_;
    buf_ = nullptr;
}

void CowString::Detach() {
    if (buf_->ref_count == 1) return;
    Buffer* fresh = new Buffer(buf_->data, buf_->size);
    --buf_->ref_count;
    buf_ = fresh;
}

//Конструкторы / деструктор

CowString::CowString()
    : buf_(new Buffer("", 0)) {}

CowString::CowString(const char* cstr)
    : buf_(nullptr) {
    if (!cstr) cstr = "";
    buf_ = new Buffer(cstr, std::strlen(cstr));
}

CowString::CowString(const std::string& s)
    : CowString(s.c_str()) {}

CowString::CowString(const CowString& other)
    : buf_(other.buf_) {
    ++buf_->ref_count;
}

CowString& CowString::operator=(const CowString& other) {
    if (this == &other) return *this;
    Release();
    buf_ = other.buf_;
    ++buf_->ref_count;
    return *this;
}

CowString::CowString(CowString&& other) noexcept
    : buf_(other.buf_) {
    other.buf_ = new Buffer("", 0);
}

CowString& CowString::operator=(CowString&& other) noexcept {
    if (this == &other) return *this;
    Release();
    buf_ = other.buf_;
    other.buf_ = new Buffer("", 0);
    return *this;
}

CowString::~CowString() {
    Release();
}

//  Методы

std::size_t CowString::Size() const {
    return buf_->size;
}

bool CowString::Empty() const {
    return buf_->size == 0;
}

const char* CowString::ToCstr() const {
    return buf_->data;
}

std::string CowString::ToString() const {
    return std::string(buf_->data);
}

const char& CowString::operator[](std::size_t i) const {
    return buf_->data[i];
}

char& CowString::operator[](std::size_t i) {
    Detach();
    return buf_->data[i];
}

CowString::operator const char*() const {
    return buf_->data;
}

CowString& CowString::Append(const char* tail) {
    if (!tail || tail[0] == '\0') return *this;

    Detach();

    const std::size_t add = std::strlen(tail);
    const std::size_t new_size = buf_->size + add;

    char* new_data = new char[new_size + 1];
    if (buf_->size) std::memcpy(new_data, buf_->data, buf_->size);
    std::memcpy(new_data + buf_->size, tail, add);
    new_data[new_size] = '\0';

    delete[] buf_->data;
    buf_->data = new_data;
    buf_->size = new_size;

    return *this;
}

CowString& CowString::Append(const std::string& tail) {
    return Append(tail.c_str());
}

CowString CowString::Substr(std::size_t pos, std::size_t count) const {
    if (pos >= buf_->size) return CowString();

    std::size_t avail = buf_->size - pos;
    std::size_t take = (count == npos || count > avail) ? avail : count;

    return CowString(std::string(buf_->data + pos, take));
}

void CowString::Clear() {
    Detach();
    delete[] buf_->data;
    buf_->data = new char[1]{'\0'};
    buf_->size = 0;
}

std::size_t CowString::Find(const char* needle) const {
    if (!needle) return npos;
    if (needle[0] == '\0') return 0;

    const char* p = std::strstr(buf_->data, needle);
    return p ? static_cast<std::size_t>(p - buf_->data) : npos;
}

std::size_t CowString::Find(const std::string& needle) const {
    return Find(needle.c_str());
}

std::size_t CowString::Find(char ch) const {
    const void* p = std::memchr(buf_->data, static_cast<unsigned char>(ch), buf_->size);
    return p ? static_cast<std::size_t>(static_cast<const char*>(p) - buf_->data) : npos;
}
