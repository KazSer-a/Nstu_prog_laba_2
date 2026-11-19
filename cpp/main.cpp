#include "tasks.h"
#include <iostream>
#include <string>
#include <unordered_map>

// Запускает выбранное задание или команду АТД «Множество» из файла.
int main(int argc, char** argv) {
    if (argc == 5 && std::string(argv[1]) == "--file" && std::string(argv[3]) == "--query") {
        setFileQuery(argv[2], argv[4], std::cout);
        return 0;
    }
    const std::unordered_map<std::string, void(*)(std::istream&, std::ostream&)> tasks = {
        {"1", taskExecutionOrder}, {"2", setCommands}, {"3", alienGenome}, {"4", stressCheck},
        {"5", treeRecovery}, {"6", hashMethods}, {"7", employeeHierarchy}, {"8", lruCache}
    };
    if (argc != 2 || !tasks.count(argv[1])) {
        std::cout << "Использование: ./laba2 <1-8> или ./laba2 --file <путь> --query '<команда>'\n";
        return 1;
    }
    tasks.at(argv[1])(std::cin, std::cout);
    return 0;
}
