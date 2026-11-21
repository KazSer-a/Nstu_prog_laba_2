#include "tasks.h"
#include "l1_structures.h"
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Приводит слово к нижнему регистру и возвращает позицию ударения.
static std::pair<std::string, int> normalizeWord(const std::string& word) {
    std::string key;
    int stress = -1;
    for (unsigned char c : word) {
        if (std::isupper(c)) stress = static_cast<int>(key.size());
        key.push_back(static_cast<char>(std::tolower(c)));
    }
    return {key, stress};
}

// Проверяет расстановку ударений в тексте с использованием динамического массива.
void stressCheck(std::istream& in, std::ostream& out) {
    int n = 0;
    if (!(in >> n) || n < 0) { out << "Неверный ввод\n"; return; }
    std::unordered_map<std::string, std::unordered_set<int>> dictionary;
    for (int i = 0; i < n; ++i) {
        std::string word;
        if (!(in >> word)) { out << "Недостаточно слов словаря\n"; return; }
        auto normalized = normalizeWord(word);
        dictionary[normalized.first].insert(normalized.second);
    }
    std::string line;
    std::getline(in, line);
    if (!std::getline(in, line)) line.clear();
    std::istringstream words(line);
    L1Array<std::string> textWords;
    std::string word;
    while (words >> word) textWords.pushBack(word);
    int errors = 0;
    for (size_t i = 0; i < textWords.size(); ++i) {
        const std::string& current = textWords.at(i);
        auto normalized = normalizeWord(current);
        int stressCount = 0;
        for (unsigned char c : current) if (std::isupper(c)) ++stressCount;
        auto found = dictionary.find(normalized.first);
        if (found == dictionary.end()) {
            if (stressCount != 1) ++errors;
        } else if (stressCount != 1 || !found->second.count(normalized.second)) {
            ++errors;
        }
    }
    out << errors << '\n';
}
