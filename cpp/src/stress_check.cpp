#include "tasks.h"
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
// Нормализует слово и определяет позицию ударения.
static std::pair<std::string,int> normalizeWord(const std::string&w){std::string k;int p=-1;for(unsigned char c:w){if(std::isupper(c))p=k.size();k.push_back((char)std::tolower(c));}return{k,p};}
// Подсчитывает ошибки расстановки ударений.
void stressCheck(std::istream&in,std::ostream&out){int n;if(!(in>>n)||n<0){out<<"Неверный ввод\n";return;}std::unordered_map<std::string,std::unordered_set<int>>d;for(int i=0;i<n;++i){std::string w;in>>w;auto p=normalizeWord(w);d[p.first].insert(p.second);}std::string line;std::getline(in,line);std::getline(in,line);std::istringstream ss(line);std::string w;int errors=0;while(ss>>w){auto p=normalizeWord(w);int c=0;for(unsigned char x:w)if(std::isupper(x))++c;auto it=d.find(p.first);if(it==d.end()){if(c!=1)++errors;}else if(c!=1||!it->second.count(p.second))++errors;}out<<errors<<'\n';}
