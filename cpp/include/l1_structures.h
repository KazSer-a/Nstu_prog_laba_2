#pragma once
#include <cstddef>
#include <string>
#include <memory>
#include <utility>

// Узел стека строк из лабораторной работы №1.
struct L1StackNode { std::string value; L1StackNode* next = nullptr; };

// Стек строк с операциями добавления и извлечения.
class L1Stack {
    L1StackNode* topNode = nullptr;
public:
    L1Stack() = default;
    L1Stack(const L1Stack&) = delete;
    L1Stack& operator=(const L1Stack&) = delete;
    // Добавляет элемент на вершину стека.
    void push(const std::string& value) { topNode = new L1StackNode{value, topNode}; }
    // Извлекает элемент с вершины стека.
    bool pop(std::string& value) { if (!topNode) return false; auto* node = topNode; value = node->value; topNode = node->next; delete node; return true; }
    // Освобождает все узлы стека.
    ~L1Stack() { std::string value; while (pop(value)) {} }
};

// Динамический массив ЛР1 с удвоением ёмкости и доступом по индексу.
template<class T>
class L1Array {
    std::size_t count = 0;
    std::size_t capacity = 0;
    std::unique_ptr<T[]> data;

public:
    L1Array() = default;
    explicit L1Array(std::size_t size)
        : count(size), capacity(size), data(std::make_unique<T[]>(size)) {}

    void pushBack(const T& value) {
        if (count == capacity) {
            const auto next = capacity ? capacity * 2 : 4;
            auto buffer = std::make_unique<T[]>(next);
            for (std::size_t i = 0; i < count; ++i) buffer[i] = data[i];
            data = std::move(buffer);
            capacity = next;
        }
        data[count] = value;
        ++count;
    }

    std::size_t size() const { return count; }
    T& at(std::size_t index) { return data[index]; }
    const T& at(std::size_t index) const { return data[index]; }

    void swap(L1Array& other) {
        std::swap(count, other.count);
        std::swap(capacity, other.capacity);
        data.swap(other.data);
    }
};

// Узел двоичного дерева поиска из лабораторной работы №1.
struct L1TreeNode { long long key; L1TreeNode* left = nullptr; L1TreeNode* right = nullptr; };

// Узел двусвязного списка из лабораторной работы №1.
struct L1DNode { std::string value; L1DNode* next = nullptr; L1DNode* prev = nullptr; };

// Двусвязный список с операциями за O(1) по указателю на узел.
class L1DList {
public:
    L1DNode* head = nullptr;
    L1DNode* tail = nullptr;
    L1DList() = default;
    L1DList(const L1DList&) = delete;
    L1DList& operator=(const L1DList&) = delete;
    // Добавляет узел в начало списка.
    L1DNode* pushFront(const std::string& value) { auto* node = new L1DNode{value, head, nullptr}; if (head) head->prev=node; else tail=node; head=node; return node; }
    // Удаляет заданный узел списка.
    void erase(L1DNode* node) { if (!node) return; if(node->prev) node->prev->next=node->next; else head=node->next; if(node->next) node->next->prev=node->prev; else tail=node->prev; delete node; }
    // Освобождает все узлы списка.
    ~L1DList() { while (head) erase(head); }
};
