#include "tasks.h"
#include <chrono>
#include <iostream>
#include <vector>
class OpenHash{std::vector<long long>keys;std::vector<bool>used;bool twice;
 // Вычисляет первый хеш.
 size_t h1(long long x)const{return(size_t)((x%(long long)keys.size()+keys.size())%keys.size());}
 // Вычисляет шаг второго хеша.
 size_t h2(long long x)const{return 1+(size_t)((x%(long long)(keys.size()-1)+keys.size()-1)%(keys.size()-1));}
public:
 // Создаёт таблицу заданного размера.
 OpenHash(size_t n,bool d):keys(n),used(n,false),twice(d){}
 // Вставляет ключ открытой адресацией.
 bool insert(long long x){size_t a=h1(x),s=twice?h2(x):1;for(size_t i=0;i<keys.size();++i){size_t p=(a+i*s)%keys.size();if(!used[p]){used[p]=true;keys[p]=x;return true;}if(keys[p]==x)return true;}return false;}
};
// Измеряет два метода хеширования на одном наборе ключей.
void hashMethods(std::istream&in,std::ostream&out){size_t n,cap;if(!(in>>n>>cap)||cap<3){out<<"Формат: N простая_ёмкость, затем N ключей\n";return;}for(size_t d=2;d*d<=cap;++d)if(cap%d==0){out<<"Размер таблицы должен быть простым числом\n";return;}std::vector<long long>v(n);for(auto&x:v)in>>x;for(bool d:{false,true}){OpenHash h(cap,d);size_t ok=0;auto start=std::chrono::steady_clock::now();for(auto x:v)if(h.insert(x))++ok;auto us=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-start).count();out<<(d?"Двойное хеширование":"Линейное апробирование")<<": вставлено "<<ok<<'/'<<n<<", время "<<us<<" мкс\n";}}
