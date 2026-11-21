#include "tasks.h"
#include "hash_table.h"

#include <chrono>
#include <iostream>
#include <vector>

void hashMethods(std::istream& in, std::ostream& out) {
    int count = 0, capacity = 0;
    if (!(in >> count >> capacity) || count < 0 || capacity < 3) {
        out << "Формат: количество_ключей простая_ёмкость_таблицы, затем ключи\n";
        return;
    }
    if (!isPrime(capacity)) {
        out << "Размер таблицы должен быть простым числом\n";
        return;
    }
    std::vector<long long> data(count);
    for (auto& value : data) {
        if (!(in >> value)) { out << "Недостаточно ключей\n"; return; }
    }
    for (bool useDoubleHash : {false, true}) {
        HashTable<long long, bool> table(capacity, useDoubleHash);
        std::size_t probes = 0;
        const auto start = std::chrono::steady_clock::now();
        for (auto value : data) probes += table.insert(value, true);
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now() - start).count();
        out << (useDoubleHash ? "Двойное хеширование" : "Линейное пробирование")
            << ": вставлено " << table.size() << '/' << count << ", проверено ячеек "
            << probes << ", время " << elapsed << " нс\n";
    }
}
