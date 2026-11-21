#pragma once

#include "l1_structures.h"

#include <cstddef>
#include <functional>
#include <string>
#include <type_traits>
#include <utility>

inline bool isPrime(std::size_t value) {
    if (value < 2) return false;
    for (std::size_t divisor = 2; divisor <= value / divisor; ++divisor) {
        if (value % divisor == 0) return false;
    }
    return true;
}

inline std::size_t nextPrime(std::size_t size) {
    while (!isPrime(size)) ++size;
    return size;
}

template<class Key, class Value>
class HashTable {
    enum class State { empty, occupied, deleted };

    struct Slot {
        Key key{};
        Value value{};
        State state = State::empty;
    };

    struct Search {
        std::size_t position;
        std::size_t probes;
        bool found;
    };

    L1Array<Slot> slots;
    bool doubleHash;
    std::size_t entries = 0;
    std::size_t used = 0;

    static std::size_t hash(const Key& key, std::size_t modulus) {
        if constexpr (std::is_signed_v<Key> && std::is_integral_v<Key>) {
            auto divisor = static_cast<Key>(modulus);
            auto remainder = key % divisor;
            return static_cast<std::size_t>(remainder < 0 ? remainder + divisor : remainder);
        } else {
            return std::hash<Key>{}(key) % modulus;
        }
    }

    Search locate(const Key& key) const {
        const auto capacity = slots.size();
        auto position = hash(key, capacity);
        const auto step = doubleHash ? 1 + hash(key, capacity - 1) : 1;
        auto firstDeleted = capacity;
        for (std::size_t probes = 1; probes <= capacity; ++probes) {
            const auto& slot = slots.at(position);
            if (slot.state == State::empty) {
                return {firstDeleted == capacity ? position : firstDeleted, probes, false};
            }
            if (slot.state == State::occupied && slot.key == key) return {position, probes, true};
            if (slot.state == State::deleted && firstDeleted == capacity) firstDeleted = position;
            position = (position + step) % capacity;
        }
        return {firstDeleted, capacity, false};
    }

public:
    HashTable(std::size_t capacity, bool useDoubleHash)
        : slots(capacity), doubleHash(useDoubleHash) {}

    std::size_t size() const { return entries; }

    // Возвращает число посещённых ячеек, включая поиск в заполненной таблице.
    std::size_t insert(const Key& key, const Value& value) {
        const auto search = locate(key);
        if (search.position == slots.size()) return search.probes;
        auto& slot = slots.at(search.position);
        if (!search.found) {
            ++entries;
            if (slot.state == State::empty) ++used;
        }
        slot = {key, value, State::occupied};
        return search.probes;
    }

    const Value* get(const Key& key) const {
        const auto search = locate(key);
        return search.found ? &slots.at(search.position).value : nullptr;
    }

    void remove(const Key& key) {
        const auto search = locate(key);
        if (!search.found) return;
        slots.at(search.position) = {Key{}, Value{}, State::deleted};
        --entries;
    }

    template<class Visit>
    void forEach(Visit visit) const {
        for (std::size_t i = 0; i < slots.size(); ++i) {
            const auto& slot = slots.at(i);
            if (slot.state == State::occupied) visit(slot.key, slot.value);
        }
    }

    // Для динамического множества. Эксперимент использует фиксированную ёмкость.
    void insertGrowing(const Key& key, const Value& value) {
        const auto capacity = slots.size();
        if (used >= capacity / 2) {
            const auto newCapacity = entries > capacity / 4
                ? nextPrime(capacity * 2) : capacity;
            HashTable rebuilt(newCapacity, doubleHash);
            forEach([&](const Key& existingKey, const Value& existingValue) {
                rebuilt.insert(existingKey, existingValue);
            });
            slots.swap(rebuilt.slots);
            used = rebuilt.used;
        }
        insert(key, value);
    }
};

class StringSet {
    HashTable<std::string, bool> values{11, true};

public:
    void add(const std::string& value) { values.insertGrowing(value, true); }
    void remove(const std::string& value) { values.remove(value); }
    bool contains(const std::string& value) const { return values.get(value) != nullptr; }
    template<class Visit>
    void forEach(Visit visit) const {
        values.forEach([&](const std::string& key, bool) { visit(key); });
    }
};
