#include "tasks.h"
#include "hash_table.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Обрабатывает команды SETADD, SETDEL и SET_AT над множеством.
void setCommands(std::istream& in, std::ostream& out) {
    int q = 0;
    if (!(in >> q) || q < 0) { out << "Неверный ввод\n"; return; }
    StringSet values;
    for (int i = 0; i < q; ++i) {
        std::string op, value;
        if (!(in >> op >> value)) { out << "Недостаточно данных\n"; return; }
        if (op == "SETADD") values.add(value);
        else if (op == "SETDEL") values.remove(value);
        else if (op == "SET_AT") out << (values.contains(value) ? "TRUE" : "FALSE") << '\n';
        else out << "Неизвестная команда\n";
    }
}

// Выполняет одну команду над множеством, сохранённым в файле.
void setFileQuery(const std::string& fileName, const std::string& query, std::ostream& out) {
    StringSet values;
    std::ifstream file(fileName);
    std::string value;
    while (file >> value) values.add(value);
    std::istringstream command(query);
    std::string op, key, extra;
    if (!(command >> op >> key) || (command >> extra)) { out << "Формат запроса: SETADD|SETDEL|SET_AT <элемент>\n"; return; }
    if (op == "SETADD") values.add(key);
    else if (op == "SETDEL") values.remove(key);
    else if (op == "SET_AT") { out << (values.contains(key) ? "TRUE" : "FALSE") << '\n'; return; }
    else { out << "Неизвестная команда\n"; return; }
    std::ofstream output(fileName, std::ios::trunc);
    if (!output) { out << "Не удалось сохранить файл\n"; return; }
    // Сохраняет отсортированные элементы множества по одному на строку.
    std::vector<std::string> items;
    values.forEach([&](const std::string& item) { items.push_back(item); });
    std::sort(items.begin(), items.end());
    for (const auto& item : items) output << item << '\n';
    out << "OK\n";
}
