#include "tasks.h"
#include <iostream>
#include <string>
#include <unordered_set>
// Считает пары первого генома, встречающиеся во втором.
void alienGenome(std::istream&in,std::ostream&out){std::string a,b;if(!(in>>a>>b)){out<<"Неверный ввод\n";return;}std::unordered_set<std::string>p;for(size_t i=1;i<b.size();++i)p.insert(b.substr(i-1,2));int ans=0;for(size_t i=1;i<a.size();++i)if(p.count(a.substr(i-1,2)))++ans;out<<ans<<'\n';}
