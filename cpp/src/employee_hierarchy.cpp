#include "tasks.h"
#include "hash_table.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Вычисляет количество потомков для всех узлов без рекурсии.
static bool calculateDescendants(const std::vector<std::string>& names,
    const std::unordered_map<std::string, std::vector<std::string>>& children,
    std::unordered_map<std::string, int>& result) {
    std::unordered_map<std::string, int> state;
    for (const auto& start : names) {
        if (state[start] == 2) continue;
        std::vector<std::pair<std::string, bool>> stack{{start, false}};
        while (!stack.empty()) {
            auto [name, expanded] = stack.back();
            stack.pop_back();
            if (expanded) {
                int total = 0;
                auto it = children.find(name);
                if (it != children.end()) {
                    for (const auto& child : it->second) total += 1 + result[child];
                }
                result[name] = total;
                state[name] = 2;
                continue;
            }
            if (state[name] == 2) continue;
            if (state[name] == 1) return false;
            state[name] = 1;
            stack.push_back({name, true});
            auto it = children.find(name);
            if (it != children.end()) {
                for (auto child = it->second.rbegin(); child != it->second.rend(); ++child) {
                    if (state[*child] == 1) return false;
                    if (state[*child] != 2) stack.push_back({*child, false});
                }
            }
        }
    }
    return true;
}

// Строит иерархию с помощью хеш-таблицы и выводит число подчинённых.
void employeeHierarchy(std::istream& in, std::ostream& out) {
    int count = 0;
    if (!(in >> count) || count < 0) { out << "Неверный ввод\n"; return; }
    HashTable<std::string, std::string> relation(nextPrime(static_cast<size_t>(count) * 2 + 3), true);
    std::vector<std::string> names;
    for (int i = 0; i < count; ++i) {
        std::string employee, manager;
        if (!(in >> employee >> manager)) { out << "Недостаточно пар сотрудников\n"; return; }
        const auto* existing = relation.get(employee);
        if (existing && *existing != manager) {
            out << "Ошибка: у сотрудника несколько менеджеров\n";
            return;
        }
        if (existing) continue;
        relation.insert(employee, manager);
        names.push_back(employee);
        names.push_back(manager);
    }
    std::sort(names.begin(), names.end());
    names.erase(std::unique(names.begin(), names.end()), names.end());
    std::unordered_map<std::string, std::vector<std::string>> children;
    for (const auto& employee : names) {
        const auto* manager = relation.get(employee);
        if (manager && *manager != employee) children[*manager].push_back(employee);
    }
    std::unordered_map<std::string, int> descendants;
    if (!calculateDescendants(names, children, descendants)) {
        out << "Ошибка: обнаружен цикл в иерархии\n";
        return;
    }
    for (const auto& name : names) out << name << ' ' << descendants[name] << '\n';
}
