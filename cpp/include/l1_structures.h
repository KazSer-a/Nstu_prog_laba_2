#pragma once
#include <cstddef>
#include <string>
#include <unordered_set>

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

// Динамический массив строк для последовательного хранения данных.
class L1Array {
    std::string* data = nullptr;
    size_t count = 0;
    size_t capacity = 0;
public:
    L1Array() = default;
    L1Array(const L1Array&) = delete;
    L1Array& operator=(const L1Array&) = delete;
    // Добавляет строку в конец массива.
    void pushBack(const std::string& value) { if (count == capacity) { size_t next = capacity ? capacity * 2 : 4; auto* buffer = new std::string[next]; for (size_t i=0;i<count;++i) buffer[i]=data[i]; delete[] data; data=buffer; capacity=next; } data[count++]=value; }
    // Возвращает число сохранённых строк.
    size_t size() const { return count; }
    // Возвращает строку по индексу.
    const std::string& at(size_t index) const { return data[index]; }
    // Освобождает память массива.
    ~L1Array() { delete[] data; }
};

// Узел двоичного дерева поиска из лабораторной работы №1.
struct L1TreeNode { long long key; L1TreeNode* left = nullptr; L1TreeNode* right = nullptr; };

// Множество строк с ожидаемыми O(1) операциями.
class L1StringSet {
    std::unordered_set<std::string> values;
public:
    // Добавляет элемент во множество.
    void add(const std::string& value) { values.insert(value); }
    // Удаляет элемент из множества.
    void remove(const std::string& value) { values.erase(value); }
    // Проверяет наличие элемента.
    bool contains(const std::string& value) const { return values.count(value) != 0; }
    // Возвращает элементы множества для сохранения.
    const std::unordered_set<std::string>& all() const { return values; }
};

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
