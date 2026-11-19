#include "tasks.h"
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
// Обрабатывает запросы SET и GET с вытеснением LRU.
void lruCache(std::istream&in,std::ostream&out){size_t cap;int q;if(!(in>>cap>>q)||q<0){out<<"Формат: ёмкость количество_запросов\n";return;}std::list<std::pair<long long,long long>>order;std::unordered_map<long long,decltype(order.begin())>idx;for(int i=0;i<q;++i){std::string op;long long x,y;in>>op>>x;if(op=="SET"){in>>y;auto it=idx.find(x);if(it!=idx.end()){it->second->second=y;order.splice(order.begin(),order,it->second);}else if(cap){if(order.size()==cap){idx.erase(order.back().first);order.pop_back();}order.emplace_front(x,y);idx[x]=order.begin();}}else if(op=="GET"){auto it=idx.find(x);if(it==idx.end())out<<-1<<' ';else{order.splice(order.begin(),order,it->second);out<<it->second->second<<' ';}}else out<<"Неизвестная команда ";}out<<'\n';}
