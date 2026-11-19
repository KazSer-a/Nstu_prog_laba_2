#include "tasks.h"
#include "l1_structures.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Находит две вершины, нарушающие порядок симметричного обхода.
static bool findSwapped(L1TreeNode* root, L1TreeNode*& first, L1TreeNode*& second) {
    std::vector<L1TreeNode*> stack;
    L1TreeNode* current = root;
    L1TreeNode* previous = nullptr;
    while (current || !stack.empty()) {
        while (current) { stack.push_back(current); current = current->left; }
        current = stack.back();
        stack.pop_back();
        if (previous && previous->key > current->key) {
            if (!first) first = previous;
            second = current;
        }
        previous = current;
        current = current->right;
    }
    return first && second;
}

// Проверяет, что симметричный обход восстановленного дерева упорядочен.
static bool isSearchTree(L1TreeNode* root) {
    std::vector<L1TreeNode*> stack;
    L1TreeNode* current = root;
    long long previous = 0;
    bool hasPrevious = false;
    while (current || !stack.empty()) {
        while (current) { stack.push_back(current); current = current->left; }
        current = stack.back(); stack.pop_back();
        if (hasPrevious && previous > current->key) return false;
        previous = current->key; hasPrevious = true; current = current->right;
    }
    return true;
}

// Освобождает узлы дерева без рекурсивного обхода.
static void destroyTree(L1TreeNode* root) {
    std::vector<L1TreeNode*> stack;
    if (root) stack.push_back(root);
    while (!stack.empty()) {
        L1TreeNode* node = stack.back(); stack.pop_back();
        if (node->left) stack.push_back(node->left);
        if (node->right) stack.push_back(node->right);
        delete node;
    }
}

// Восстанавливает BST, меняя только значения двух узлов.
void treeRecovery(std::istream& in, std::ostream& out) {
    std::string line;
    if (!std::getline(in >> std::ws, line)) { out << "Неверный ввод\n"; return; }
    std::istringstream input(line);
    std::vector<std::string> tokens;
    std::string token;
    while (input >> token) tokens.push_back(token);
    if (tokens.empty() || tokens.front() == "#") { out << "Пустое дерево\n"; return; }
    L1TreeNode* root = nullptr;
    auto parseKey = [](const std::string& value) {
        size_t consumed = 0;
        long long key = std::stoll(value, &consumed);
        if (consumed != value.size()) throw std::invalid_argument("неверный ключ");
        return key;
    };
    try {
        root = new L1TreeNode{parseKey(tokens[0]), nullptr, nullptr};
        std::vector<L1TreeNode*> nodes{root};
        size_t pos = 1;
        for (size_t i = 0; i < nodes.size() && pos < tokens.size(); ++i) {
            if (tokens[pos] != "#") {
                nodes[i]->left = new L1TreeNode{parseKey(tokens[pos]), nullptr, nullptr};
                nodes.push_back(nodes[i]->left);
            }
            ++pos;
            if (pos < tokens.size() && tokens[pos] != "#") {
                nodes[i]->right = new L1TreeNode{parseKey(tokens[pos]), nullptr, nullptr};
                nodes.push_back(nodes[i]->right);
            }
            ++pos;
        }
        if (pos < tokens.size()) throw std::invalid_argument("лишние узлы");
    } catch (const std::exception&) {
        destroyTree(root);
        out << "Неверное представление дерева\n";
        return;
    }
    L1TreeNode *first = nullptr, *second = nullptr;
    if (!findSwapped(root, first, second)) {
        destroyTree(root);
        out << "Не найдены два перепутанных узла\n";
        return;
    }
    std::swap(first->key, second->key);
    if (!isSearchTree(root)) {
        std::swap(first->key, second->key);
        destroyTree(root);
        out << "Не удалось восстановить дерево\n";
        return;
    }
    std::queue<L1TreeNode*> queue;
    queue.push(root);
    std::vector<std::string> result;
    while (!queue.empty()) {
        L1TreeNode* node = queue.front(); queue.pop();
        if (!node) { result.push_back("#"); continue; }
        result.push_back(std::to_string(node->key));
        queue.push(node->left);
        queue.push(node->right);
    }
    while (!result.empty() && result.back() == "#") result.pop_back();
    for (size_t i = 0; i < result.size(); ++i) out << (i ? " " : "") << result[i];
    out << '\n';
    destroyTree(root);
}
