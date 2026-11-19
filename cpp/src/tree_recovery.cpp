#include "tasks.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
struct Node{long long key;Node*left=nullptr;Node*right=nullptr;};
// Находит две вершины, нарушающие порядок симметричного обхода.
static void findSwapped(Node*n,Node*&prev,Node*&a,Node*&b){if(!n)return;findSwapped(n->left,prev,a,b);if(prev&&prev->key>n->key){if(!a)a=prev;b=n;}prev=n;findSwapped(n->right,prev,a,b);}
// Освобождает память дерева.
static void destroyTree(Node*n){if(!n)return;destroyTree(n->left);destroyTree(n->right);delete n;}
// Восстанавливает BST, меняя только значения двух узлов.
void treeRecovery(std::istream&in,std::ostream&out){std::string line;std::getline(in>>std::ws,line);std::istringstream ss(line);std::vector<std::string>t;std::string x;while(ss>>x)t.push_back(x);if(t.empty()||t[0]=="#"){out<<"Пустое дерево\n";return;}std::vector<Node*>nodes;nodes.push_back(new Node{std::stoll(t[0])});size_t p=1;for(size_t i=0;i<nodes.size()&&p<t.size();++i){if(p<t.size()&&t[p]!="#"){nodes[i]->left=new Node{std::stoll(t[p])};nodes.push_back(nodes[i]->left);}++p;if(p<t.size()&&t[p]!="#"){nodes[i]->right=new Node{std::stoll(t[p])};nodes.push_back(nodes[i]->right);}++p;}Node*prev=nullptr,*a=nullptr,*b=nullptr;findSwapped(nodes[0],prev,a,b);if(a&&b)std::swap(a->key,b->key);std::queue<Node*>q;q.push(nodes[0]);std::vector<std::string>v;while(!q.empty()){auto n=q.front();q.pop();if(!n){v.push_back("#");continue;}v.push_back(std::to_string(n->key));q.push(n->left);q.push(n->right);}while(!v.empty()&&v.back()=="#")v.pop_back();for(size_t i=0;i<v.size();++i)out<<(i?" ":"")<<v[i];out<<'\n';destroyTree(nodes[0]);}
