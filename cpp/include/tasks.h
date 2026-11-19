#pragma once
#include <iosfwd>
// Проверяет возможность выполнить задачи с зависимостями.
void taskExecutionOrder(std::istream&, std::ostream&);
// Выполняет команды над множеством.
void setCommands(std::istream&, std::ostream&);
// Вычисляет степень близости геномов.
void alienGenome(std::istream&, std::ostream&);
// Проверяет правильность ударений в тексте.
void stressCheck(std::istream&, std::ostream&);
// Восстанавливает значения двух перепутанных узлов BST.
void treeRecovery(std::istream&, std::ostream&);
// Сравнивает два метода разрешения коллизий.
void hashMethods(std::istream&, std::ostream&);
// Подсчитывает число подчинённых в иерархии.
void employeeHierarchy(std::istream&, std::ostream&);
// Выполняет запросы к LRU-кэшу.
void lruCache(std::istream&, std::ostream&);
