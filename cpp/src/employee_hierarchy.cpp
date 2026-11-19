#include "tasks.h"
#include "hash_table.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
// Считает всех потомков сотрудника.
static int countDesc(const std::string&n,const std::unordered_map<std::string,std::vector<std::string>>&c,std::unordered_map<std::string,int>&memo){auto it=memo.find(n);if(it!=memo.end())return it->second;int total=0;auto x=c.find(n);if(x!=c.end())for(auto&s:x->second)total+=1+countDesc(s,c,memo);return memo[n]=total;}
// Строит иерархию через хеш-таблицу и выводит число подчинённых.
void employeeHierarchy(std::istream&in,std::ostream&out){int n;if(!(in>>n)||n<0){out<<"Неверный ввод\n";return;}std::vector<std::pair<std::string,std::string>>r;std::vector<std::string>names;for(int i=0;i<n;++i){std::string e,m;in>>e>>m;r.push_back({e,m});names.push_back(e);if(e==m)names.push_back(m);}StringHashTable table(n*2+3,true);for(auto&p:r)table.insert(p.first,p.second);std::unordered_map<std::string,std::vector<std::string>>children;for(auto&p:r){std::string m;if(table.get(p.first,m)&&p.first!=m)children[m].push_back(p.first);}std::sort(names.begin(),names.end());names.erase(std::unique(names.begin(),names.end()),names.end());std::unordered_map<std::string,int>memo;for(auto&name:names)out<<name<<' '<<countDesc(name,children,memo)<<'\n';}
