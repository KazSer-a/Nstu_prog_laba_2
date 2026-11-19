#include "tasks.h"
#include <iostream>
#include <string>
#include <unordered_set>
// Обрабатывает команды SETADD, SETDEL и SET_AT.
void setCommands(std::istream&in,std::ostream&out){int q;if(!(in>>q)||q<0){out<<"Неверный ввод\n";return;}std::unordered_set<std::string>s;for(int i=0;i<q;++i){std::string op,x;in>>op>>x;if(op=="SETADD")s.insert(x);else if(op=="SETDEL")s.erase(x);else if(op=="SET_AT")out<<(s.count(x)?"TRUE":"FALSE")<<'\n';else out<<"Неизвестная команда\n";}}
