#include <string>
#include <utility>

class Tracer {
public:
    // Счетчики (доступны извне)
    inline static int count = 0;         // сколько объектов когда-либо создано (и генератор id)
    inline static int default_ctor = 0;
    inline static int str_ctor = 0;
    inline static int copy_ctor = 0;
    inline static int move_ctor = 0;
    inline static int copy_assign = 0;
    inline static int move_assign = 0;
    inline static int dtor = 0;
    inline static int alive = 0;

    // Конструктор по умолчанию
    Tracer() : id_(NextId()), name_("obj_" + std::to_string(id_)) {
        ++default_ctor;
        ++alive;
    }

    // Конструктор от строки std::string
    Tracer(const std::string& base_name) : id_(NextId()), name_(base_name + "_" + std::to_string(id_)) {
        ++str_ctor;
        ++alive;
    }

    // Конструктор от C-строки 
    Tracer(const char* base_name) : Tracer(std::string(base_name ? base_name : "")) {}

    // Копирующий конструктор: копирует имя, но создаёт новый id
    Tracer(const Tracer& other) : id_(NextId()), name_(other.name_) {
        ++copy_ctor;
        ++alive;
    }

    // Перемещающий конструктор: перемещает имя, но создаёт новый id
    Tracer(Tracer&& other) noexcept : id_(NextId()), name_(std::move(other.name_)) {
        ++move_ctor;
        ++alive;
    }

    // Копирующее присваивание: копирует имя, id не меняется
    Tracer& operator=(const Tracer& other) {
        if (this == &other) {
            return *this; // self-assignment: не считаем, не меняем
        }
        name_ = other.name_;
        ++copy_assign;
        return *this;
    }

    // Перемещающее присваивание: перемещает имя, id не меняется
    Tracer& operator=(Tracer&& other) noexcept {
        if (this == &other) {
            return *this; // self-move: не считаем, не меняем
        }
        name_ = std::move(other.name_);
        ++move_assign;
        return *this;
    }

    // Деструктор
    ~Tracer() {
        ++dtor;
        --alive;
    }

    // Id, Name, Data
    int Id() const { return id_; }
    const std::string& Name() const { return name_; }
    const char* Data() const { return name_.c_str(); }

    // Сброс статистики
    static void ResetStats() {
        count = 0;
        default_ctor = 0;
        str_ctor = 0;
        copy_ctor = 0;
        move_ctor = 0;
        copy_assign = 0;
        move_assign = 0;
        dtor = 0;
        alive = 0;
    }

private:
    int id_;
    std::string name_;

    static int NextId() {
        return ++count; // id начинается с 1
    }
};
