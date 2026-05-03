// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* head;
    Node* tail;
public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    ~TPQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void push(const T& item) {
        Node* newNode = new Node(item);
        // Если очередь пуста или новый элемент имеет наивысший приоритет
        if (!head || head->data.prior < item.prior) {
            newNode->next = head;
            head = newNode;
            if (!tail) tail = head;
            return;
        }
        // Поиск места для вставки (сохранение порядка по убыванию приоритета)
        Node* current = head;
        while (current->next && current->next->data.prior >= item.prior) {
            current = current->next;
        }
        // Вставка после current
        newNode->next = current->next;
        current->next = newNode;
        // Обновление tail, если вставили в конец
        if (!newNode->next) tail = newNode;
    }
    T pop() {
        if (!head) {
            // Возвращаем пустую структуру, если очередь пуста
            T empty{};
            return empty;
        }
        Node* temp = head;
        T result = head->data;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        return result;
    }
    // Дополнительный метод для проверки, пуста ли очередь
    bool isEmpty() const {
        return head == nullptr;
    }
};
#endif  // INCLUDE_TPQUEUE_H_
