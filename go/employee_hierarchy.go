package main
import("bufio";"fmt";"sort")
// Считает всех потомков сотрудника.
func countDesc(name string,c map[string][]string,memo map[string]int)int{if v,ok:=memo[name];ok{return v};n:=0;for _,x:=range c[name]{n+=1+countDesc(x,c,memo)};memo[name]=n;return n}
// Строит иерархию через хеш-таблицу и выводит число подчинённых.
func employeeHierarchy(in *bufio.Reader,out *bufio.Writer){var n int;if _,e:=fmt.Fscan(in,&n);e!=nil||n<0{fmt.Fprintln(out,"Неверный ввод");return};h:=newStringHashTable(n*2+3,true);names:=map[string]bool{};pairs:=make([][2]string,n);for i:=range pairs{fmt.Fscan(in,&pairs[i][0],&pairs[i][1]);names[pairs[i][0]]=true;if pairs[i][0]==pairs[i][1]{names[pairs[i][1]]=true};h.insert(pairs[i][0],pairs[i][1])};children:=map[string][]string{};for _,p:=range pairs{m,ok:=h.get(p[0]);if ok&&m!=p[0]{children[m]=append(children[m],p[0])}};list:=[]string{};for s:=range names{list=append(list,s)};sort.Strings(list);memo:=map[string]int{};for _,s:=range list{fmt.Fprintln(out,s,countDesc(s,children,memo))}}
