#include "tasks.h"
#include <chrono>
#include <iostream>
#include <vector>

class OpenHash {
    std::vector<long long> keys;
    std::vector<bool> used;
    bool doubleHash;
    // Вычисляет неотрицательный остаток от деления ключа.
    static size_t positiveMod(long long value, size_t mod) {
        long long remainder = value % static_cast<long long>(mod);
        if (remainder < 0) remainder += static_cast<long long>(mod);
        return static_cast<size_t>(remainder);
    }
    // Вычисляет начальный индекс ключа.
    size_t hash1(long long value) const { return positiveMod(value, keys.size()); }
    // Вычисляет шаг двойного хеширования.
    size_t hash2(long long value) const { return 1 + positiveMod(value, keys.size() - 1); }
public:
    // Создаёт таблицу заданного размера.
    OpenHash(size_t capacity, bool useDoubleHash) : keys(capacity), used(capacity, false), doubleHash(useDoubleHash) {}
    // Вставляет ключ с выбранной последовательностью проб.
    bool insert(long long value) {
        size_t start = hash1(value);
        size_t step = doubleHash ? hash2(value) : 1;
        for (size_t i = 0; i < keys.size(); ++i) {
            size_t position = (start + i * step) % keys.size();
            if (!used[position]) { used[position] = true; keys[position] = value; return true; }
            if (keys[position] == value) return true;
        }
        return false;
    }
};

// Измеряет линейное апробирование и двойное хеширование на одинаковом наборе ключей.
void hashMethods(std::istream& in, std::ostream& out) {
    size_t count = 0, capacity = 0;
    if (!(in >> count >> capacity) || capacity < 3) {
        out << "Формат: количество_ключей простая_ёмкость_таблицы, затем ключи\n";
        return;
    }
    for (size_t divisor = 2; divisor <= capacity / divisor; ++divisor) {
        if (capacity % divisor == 0) { out << "Размер таблицы должен быть простым числом\n"; return; }
    }
    std::vector<long long> data(count);
    for (auto& value : data) {
        if (!(in >> value)) { out << "Недостаточно ключей\n"; return; }
    }
    for (bool useDoubleHash : {false, true}) {
        OpenHash table(capacity, useDoubleHash);
        size_t inserted = 0;
        auto start = std::chrono::steady_clock::now();
        for (long long value : data) if (table.insert(value)) ++inserted;
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
        out << (useDoubleHash ? "Двойное хеширование" : "Линейное апробирование")
            << ": вставлено " << inserted << '/' << count << ", время " << elapsed << " мкс\n";
    }
}
