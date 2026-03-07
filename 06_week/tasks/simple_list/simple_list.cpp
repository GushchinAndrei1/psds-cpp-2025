#include <string>

class SimpleList {

    // Узел двусвязного списка
    struct Node {
        std::string value; // значение
        Node* next;        // следующий элемент
        Node* prev;        // предыдущий элемент

        Node(const std::string& v) : value(v), next(nullptr), prev(nullptr) {}
        Node(std::string&& v) : value(std::move(v)), next(nullptr), prev(nullptr) {}
    };

    Node* head = nullptr; // первый элемент списка
    Node* tail = nullptr; // последний элемент списка
    size_t size_ = 0;     // количество элементов

public:

    SimpleList() = default; // конструктор

    ~SimpleList() { Clear(); } // освобождение памяти

    // конструктор копирования
    SimpleList(const SimpleList& other) {
        for (Node* cur = other.head; cur; cur = cur->next)
            PushBack(cur->value);
    }

    // конструктор перемещения
    SimpleList(SimpleList&& other) noexcept
        : head(other.head), tail(other.tail), size_(other.size_) {

        other.head = other.tail = nullptr;
        other.size_ = 0;
    }

    // оператор копирующего присваивания
    SimpleList& operator=(const SimpleList& other) {

        if (this != &other) {
            Clear();
            for (Node* cur = other.head; cur; cur = cur->next)
                PushBack(cur->value);
        }

        return *this;
    }

    // оператор перемещающего присваивания
    SimpleList& operator=(SimpleList&& other) noexcept {

        if (this != &other) {

            Clear();

            head = other.head;
            tail = other.tail;
            size_ = other.size_;

            other.head = other.tail = nullptr;
            other.size_ = 0;
        }

        return *this;
    }

    // обмен содержимым списков
    void Swap(SimpleList& other) {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size_, other.size_);
    }

    size_t Size() const { return size_; } // вернуть размер

    bool Empty() const { return size_ == 0; } // список пуст

    // вставка в конец
    void PushBack(const std::string& v) {

        Node* n = new Node(v);

        if (!tail)
            head = tail = n;
        else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }

        ++size_;
    }

    // вставка в конец (перемещение)
    void PushBack(std::string&& v) {

        Node* n = new Node(std::move(v));

        if (!tail)
            head = tail = n;
        else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }

        ++size_;
    }

    // вставка в начало
    void PushFront(const std::string& v) {

        Node* n = new Node(v);

        if (!head)
            head = tail = n;
        else {
            n->next = head;
            head->prev = n;
            head = n;
        }

        ++size_;
    }

    // вставка в начало (перемещение)
    void PushFront(std::string&& v) {

        Node* n = new Node(std::move(v));

        if (!head)
            head = tail = n;
        else {
            n->next = head;
            head->prev = n;
            head = n;
        }

        ++size_;
    }

    // удалить последний элемент
    void PopBack() {

        if (!tail) return;

        Node* t = tail;
        tail = tail->prev;

        if (tail) tail->next = nullptr;
        else head = nullptr;

        delete t;
        --size_;
    }

    // удалить первый элемент
    void PopFront() {

        if (!head) return;

        Node* h = head;
        head = head->next;

        if (head) head->prev = nullptr;
        else tail = nullptr;

        delete h;
        --size_;
    }

    std::string& Front() { return head->value; } // первый элемент
    const std::string& Front() const { return head->value; }

    std::string& Back() { return tail->value; } // последний элемент
    const std::string& Back() const { return tail->value; }

    // очистить список
    void Clear() {
        while (head) PopFront();
    }
};

// внешний Swap
inline void Swap(SimpleList& a, SimpleList& b) {
    a.Swap(b);
}