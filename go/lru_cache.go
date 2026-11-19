package main

import (
    "bufio"
    "fmt"
    "strconv"
    "strings"
)

// Кодирует пару ключ-значение для хранения в узле двусвязного списка.
func encodeCacheEntry(key,value int64) string { return strconv.FormatInt(key,10)+"|"+strconv.FormatInt(value,10) }

// Извлекает значение из записи кэша.
func decodeCacheValue(entry string) int64 { parts:=strings.SplitN(entry,"|",2); value,_:=strconv.ParseInt(parts[1],10,64); return value }

// Выполняет SET и GET с вытеснением наименее недавно использованного ключа.
func lruCache(in *bufio.Reader,out *bufio.Writer) {
    var capacity,q int
    if _,err:=fmt.Fscan(in,&capacity,&q); err!=nil || capacity<0 || q<0 { fmt.Fprintln(out,"Формат: ёмкость количество_запросов"); return }
    var order l1DList; index:=make(map[int64]*l1DNode)
    for i:=0;i<q;i++ {
        var op string; var key,value int64
        if _,err:=fmt.Fscan(in,&op,&key); err!=nil { fmt.Fprintln(out,"Недостаточно запросов"); return }
        switch op {
        case "SET":
            if _,err:=fmt.Fscan(in,&value); err!=nil { fmt.Fprintln(out,"Не указано значение SET"); return }
            if node,ok:=index[key]; ok { entry:=encodeCacheEntry(key,value); order.erase(node); index[key]=order.pushFront(entry) } else if capacity>0 {
                if len(index)==capacity { old:=order.tail; fields:=strings.SplitN(old.value,"|",2); oldKey,_:=strconv.ParseInt(fields[0],10,64); delete(index,oldKey); order.erase(old) }
                index[key]=order.pushFront(encodeCacheEntry(key,value))
            }
        case "GET":
            if node,ok:=index[key]; ok { result:=decodeCacheValue(node.value); entry:=node.value; order.erase(node); index[key]=order.pushFront(entry); fmt.Fprint(out,result," ") } else { fmt.Fprint(out,"-1 ") }
        default: fmt.Fprint(out,"Неизвестная команда ")
        }
    }
    fmt.Fprintln(out)
}
