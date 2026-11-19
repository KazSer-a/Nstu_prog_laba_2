#include "tasks.h"
#include "l1_structures.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Проверяет возможность завершить все задачи топологической сортировкой со стеком.
void taskExecutionOrder(std::istream& in, std::ostream& out) {
    int n = 0, m = 0;
    if (!(in >> n >> m) || n < 0 || m < 0) { out << "Неверный ввод\n"; return; }
    std::unordered_map<std::string, int> ids;
    std::vector<std::vector<int>> graph;
    std::vector<int> indegree;
    auto getId = [&](const std::string& name) {
        auto it = ids.find(name);
        if (it != ids.end()) return it->second;
        int id = static_cast<int>(ids.size());
        ids[name] = id;
        graph.emplace_back();
        indegree.push_back(0);
        return id;
    };
    for (int i = 0; i < n; ++i) {
        std::string name;
        if (!(in >> name)) { out << "Недостаточно имён задач\n"; return; }
        getId(name);
    }
    for (int i = 0; i < m; ++i) {
        std::string task, prerequisite;
        if (!(in >> task >> prerequisite)) { out << "Недостаточно зависимостей\n"; return; }
        int from = getId(prerequisite);
        int to = getId(task);
        graph[from].push_back(to);
        ++indegree[to];
    }
    L1Stack stack;
    for (int i = 0; i < static_cast<int>(indegree.size()); ++i)
        if (indegree[i] == 0) stack.push(std::to_string(i));
    int completed = 0;
    std::string item;
    while (stack.pop(item)) {
        int vertex = std::stoi(item);
        ++completed;
        for (int next : graph[vertex])
            if (--indegree[next] == 0) stack.push(std::to_string(next));
    }
    out << (completed == static_cast<int>(indegree.size()) ? "Возможно" : "Невозможно") << '\n';
}
