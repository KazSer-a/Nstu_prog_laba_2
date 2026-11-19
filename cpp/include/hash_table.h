#pragma once
#include <cstddef>
#include <functional>
#include <string>
#include <vector>
class StringHashTable {
 struct Slot { std::string key,value; bool used=false; };
 std::vector<Slot> slots; bool doubleHash;
 // Подбирает простую ёмкость таблицы.
 static size_t nextPrime(size_t n){auto prime=[](size_t x){if(x<2)return false;for(size_t d=2;d*d<=x;++d)if(x%d==0)return false;return true;};while(!prime(n))++n;return n;}
 // Вычисляет начальный индекс ключа.
 size_t firstHash(const std::string&k)const{return std::hash<std::string>{}(k)%slots.size();}
 // Вычисляет шаг двойного хеширования.
 size_t secondHash(const std::string&k)const{return 1+std::hash<std::string>{}(k)%(slots.size()-1);}
public:
 // Создаёт таблицу с выбранным методом.
 explicit StringHashTable(size_t n,bool d=false):slots(nextPrime(n<3?3:n)),doubleHash(d){}
 // Добавляет пару или обновляет значение.
 bool insert(const std::string&k,const std::string&v){size_t h=firstHash(k),s=doubleHash?secondHash(k):1;for(size_t i=0;i<slots.size();++i){auto&x=slots[(h+i*s)%slots.size()];if(!x.used||x.key==k){x={k,v,true};return true;}}return false;}
 // Возвращает значение по ключу.
 bool get(const std::string&k,std::string&v)const{size_t h=firstHash(k),s=doubleHash?secondHash(k):1;for(size_t i=0;i<slots.size();++i){const auto&x=slots[(h+i*s)%slots.size()];if(!x.used)return false;if(x.key==k){v=x.value;return true;}}return false;}
};
