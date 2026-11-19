#include "tasks.h"
#include "l1_structures.h"
#include <iostream>
#include <string>
#include <unordered_map>

// Кодирует ключ и значение кэш-элемента для хранения в двусвязном списке.
static std::string encodeEntry(long long key, long long value) { return std::to_string(key) + "|" + std::to_string(value); }
// Извлекает значение из записи двусвязного списка.
static long long decodeValue(const std::string& entry) { return std::stoll(entry.substr(entry.find('|') + 1)); }

// Выполняет SET и GET с вытеснением наименее недавно использованного ключа.
void lruCache(std::istream& in, std::ostream& out) {
    size_t capacity = 0;
    int queries = 0;
    if (!(in >> capacity >> queries) || queries < 0) { out << "Формат: ёмкость количество_запросов\n"; return; }
    L1DList order;
    std::unordered_map<long long, L1DNode*> index;
    for (int i = 0; i < queries; ++i) {
        std::string operation;
        long long key = 0, value = 0;
        if (!(in >> operation >> key)) { out << "Недостаточно запросов\n"; return; }
        if (operation == "SET") {
            if (!(in >> value)) { out << "Не указано значение SET\n"; return; }
            auto found = index.find(key);
            if (found != index.end()) {
                std::string entry = encodeEntry(key, value);
                L1DNode* node = found->second;
                order.erase(node);
                index[key] = order.pushFront(entry);
            } else if (capacity > 0) {
                if (index.size() == capacity) {
                    L1DNode* leastRecent = order.tail;
                    long long removedKey = std::stoll(leastRecent->value.substr(0, leastRecent->value.find('|')));
                    index.erase(removedKey);
                    order.erase(leastRecent);
                }
                index[key] = order.pushFront(encodeEntry(key, value));
            }
        } else if (operation == "GET") {
            auto found = index.find(key);
            if (found == index.end()) out << -1 << ' ';
            else {
                long long cachedValue = decodeValue(found->second->value);
                std::string entry = found->second->value;
                order.erase(found->second);
                index[key] = order.pushFront(entry);
                out << cachedValue << ' ';
            }
        } else out << "Неизвестная команда ";
    }
    out << '\n';
}
