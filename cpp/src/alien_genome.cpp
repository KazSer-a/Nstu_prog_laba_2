#include "tasks.h"
#include "l1_structures.h"
#include <iostream>
#include <string>

// Считает пары первого генома, присутствующие во втором геноме.
void alienGenome(std::istream& in, std::ostream& out) {
    std::string first, second;
    if (!(in >> first >> second)) { out << "Неверный ввод\n"; return; }
    L1StringSet pairs;
    for (size_t i = 1; i < second.size(); ++i) pairs.add(second.substr(i - 1, 2));
    int answer = 0;
    for (size_t i = 1; i < first.size(); ++i)
        if (pairs.contains(first.substr(i - 1, 2))) ++answer;
    out << answer << '\n';
}
