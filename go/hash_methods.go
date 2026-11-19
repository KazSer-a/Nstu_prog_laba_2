package main

import (
    "bufio"
    "fmt"
    "time"
)

type openHash struct { keys []int64; used []bool; double bool }

// Создаёт таблицу заданного размера и выбранного метода.
func newOpenHash(size int, double bool) *openHash { return &openHash{keys:make([]int64,size), used:make([]bool,size), double:double} }

// Вычисляет неотрицательный остаток от деления ключа.
func positiveMod(value int64, mod int64) int64 { r:=value%mod; if r<0 { r+=mod }; return r }

// Вставляет ключ с линейным или двойным пробированием.
func (h *openHash) insert(value int64) bool {
    n:=int64(len(h.keys)); start:=positiveMod(value,n); step:=int64(1); if h.double { step=1+positiveMod(value,n-1) }
    for i:=int64(0); i<n; i++ { pos:=int((start+i*step)%n); if !h.used[pos] { h.used[pos]=true; h.keys[pos]=value; return true }; if h.keys[pos]==value { return true } }
    return false
}

// Проверяет размер таблицы и сравнивает время двух методов.
func hashMethods(in *bufio.Reader, out *bufio.Writer) {
    var count,size int
    if _,err:=fmt.Fscan(in,&count,&size); err!=nil || count<0 || size<3 { fmt.Fprintln(out,"Формат: количество_ключей простая_ёмкость_таблицы, затем ключи"); return }
    if !isPrime(size) { fmt.Fprintln(out,"Размер таблицы должен быть простым числом"); return }
    data:=make([]int64,count); for i:=range data { if _,err:=fmt.Fscan(in,&data[i]); err!=nil { fmt.Fprintln(out,"Недостаточно ключей"); return } }
    for _,double:=range []bool{false,true} { table:=newOpenHash(size,double); inserted:=0; start:=time.Now(); for _,value:=range data { if table.insert(value) { inserted++ } }; elapsed:=time.Since(start); name:="Линейное апробирование"; if double { name="Двойное хеширование" }; fmt.Fprintf(out,"%s: вставлено %d/%d, время %s\n",name,inserted,count,elapsed) }
}
