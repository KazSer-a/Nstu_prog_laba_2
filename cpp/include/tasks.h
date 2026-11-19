#pragma once
#include <iosfwd>
#include <string>

// Проверяет возможность выполнить все задачи с заданными зависимостями.
void taskExecutionOrder(std::istream& in, std::ostream& out);
// Выполняет команды добавления, удаления и проверки множества.
void setCommands(std::istream& in, std::ostream& out);
// Выполняет запрос к множеству, сохранённому в файле.
void setFileQuery(const std::string& fileName, const std::string& query, std::ostream& out);
// Вычисляет степень близости двух геномов.
void alienGenome(std::istream& in, std::ostream& out);
// Проверяет правильность ударений в тексте.
void stressCheck(std::istream& in, std::ostream& out);
// Восстанавливает значения двух перепутанных узлов дерева поиска.
void treeRecovery(std::istream& in, std::ostream& out);
// Сравнивает линейное апробирование и двойное хеширование.
void hashMethods(std::istream& in, std::ostream& out);
// Подсчитывает всех подчинённых каждого сотрудника.
void employeeHierarchy(std::istream& in, std::ostream& out);
// Выполняет запросы к LRU-кэшу.
void lruCache(std::istream& in, std::ostream& out);
