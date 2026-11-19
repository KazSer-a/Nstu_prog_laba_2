#include "tasks.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
// Проверяет возможность завершить задачи алгоритмом Кана.
void taskExecutionOrder(std::istream&in,std::ostream&out){
 int n,m;if(!(in>>n>>m)||n<0||m<0){out<<"Неверный ввод\n";return;}std::unordered_map<std::string,int>ids;std::vector<std::vector<int>>g;std::vector<int>d;
 auto id=[&](const std::string&s){auto it=ids.find(s);if(it!=ids.end())return it->second;int v=ids.size();ids[s]=v;g.emplace_back();d.push_back(0);return v;};
 for(int i=0;i<n;++i){std::string s;in>>s;id(s);}for(int i=0;i<m;++i){std::string a,b;in>>a>>b;int x=id(b),y=id(a);g[x].push_back(y);++d[y];}
 std::vector<int>st;for(int i=0;i<(int)d.size();++i)if(!d[i])st.push_back(i);int done=0;while(!st.empty()){int v=st.back();st.pop_back();++done;for(int x:g[v])if(--d[x]==0)st.push_back(x);}out<<(done==(int)d.size()?"Возможно":"Невозможно")<<'\n';
}
