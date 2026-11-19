#include "tasks.h"
#include <iostream>
#include <string>
#include <unordered_map>
// Запускает выбранное лабораторное задание.
int main(int argc,char**argv){
 const std::unordered_map<std::string,void(*)(std::istream&,std::ostream&)> t={{"1",taskExecutionOrder},{"2",setCommands},{"3",alienGenome},{"4",stressCheck},{"5",treeRecovery},{"6",hashMethods},{"7",employeeHierarchy},{"8",lruCache}};
 if(argc!=2||!t.count(argv[1])){std::cout<<"Использование: ./laba2 <1-8>\n";return 1;}t.at(argv[1])(std::cin,std::cout);return 0;
}
