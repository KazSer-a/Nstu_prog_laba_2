package main

import (
    "bufio"
    "fmt"
    "sort"
)

// Подсчитывает всех потомков узлов итеративным обходом дерева.
func calculateEmployeeCounts(names []string, children map[string][]string) (map[string]int, bool) {
    state:=make(map[string]int); result:=make(map[string]int)
    for _,start:=range names {
        if state[start]==2 { continue }
        type frame struct{name string; expanded bool}
        stack:=[]frame{{start,false}}
        for len(stack)>0 {
            f:=stack[len(stack)-1]; stack=stack[:len(stack)-1]
            if f.expanded { total:=0; for _,child:=range children[f.name] { total+=1+result[child] }; result[f.name]=total; state[f.name]=2; continue }
            if state[f.name]==2 { continue }; if state[f.name]==1 { return nil,false }; state[f.name]=1; stack=append(stack,frame{f.name,true})
            for i:=len(children[f.name])-1;i>=0;i-- { child:=children[f.name][i]; if state[child]==1 { return nil,false }; if state[child]!=2 { stack=append(stack,frame{child,false}) } }
        }
    }
    return result,true
}

// Строит иерархию через хеш-таблицу и выводит число подчинённых.
func employeeHierarchy(in *bufio.Reader, out *bufio.Writer) {
    var count int
    if _,err:=fmt.Fscan(in,&count); err!=nil || count<0 { fmt.Fprintln(out,"Неверный ввод"); return }
    relation := newHashTable[string, string](nextPrime(count*2+3), true, stringHash)
    namesSet := make(map[string]bool)
    for i := 0; i < count; i++ {
        var employee, manager string
        if _, err := fmt.Fscan(in, &employee, &manager); err != nil {
            fmt.Fprintln(out, "Недостаточно пар сотрудников")
            return
        }
        if existing, found := relation.get(employee); found {
            if existing != manager {
                fmt.Fprintln(out, "Ошибка: у сотрудника несколько менеджеров")
                return
            }
            continue
        }
        relation.insert(employee, manager)
        namesSet[employee], namesSet[manager] = true, true
    }
    children := make(map[string][]string)
    relation.forEach(func(employee, manager string) {
        if employee != manager {
            children[manager] = append(children[manager], employee)
        }
    })
    names := make([]string, 0, len(namesSet))
    for name := range namesSet {
        names = append(names, name)
    }
    sort.Strings(names)
    result,ok:=calculateEmployeeCounts(names,children); if !ok { fmt.Fprintln(out,"Ошибка: обнаружен цикл в иерархии"); return }
    for _,name:=range names { fmt.Fprintln(out,name,result[name]) }
}
