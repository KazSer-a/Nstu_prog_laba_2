package main
import "hash/fnv"
type hashSlot struct{key,value string;used bool}
type stringHashTable struct{slots []hashSlot;double bool}
// Проверяет простоту числа.
func isPrime(n int)bool{if n<2{return false};for d:=2;d*d<=n;d++{if n%d==0{return false}};return true}
// Подбирает простую ёмкость и создаёт таблицу.
func newStringHashTable(n int,d bool)*stringHashTable{if n<3{n=3};for !isPrime(n){n++};return &stringHashTable{slots:make([]hashSlot,n),double:d}}
// Вычисляет хеш-сумму строки.
func stringHash(s string)uint64{h:=fnv.New64a();_,_=h.Write([]byte(s));return h.Sum64()}
// Добавляет пару или обновляет существующий ключ.
func(h *stringHashTable)insert(k,v string)bool{n:=len(h.slots);a:=stringHash(k)%uint64(n);step:=uint64(1);if h.double{step=1+stringHash(k)%uint64(n-1)};for i:=0;i<n;i++{p:=(a+uint64(i)*step)%uint64(n);s:=&h.slots[p];if !s.used||s.key==k{*s=hashSlot{k,v,true};return true}};return false}
// Возвращает значение по ключу.
func(h *stringHashTable)get(k string)(string,bool){n:=len(h.slots);a:=stringHash(k)%uint64(n);step:=uint64(1);if h.double{step=1+stringHash(k)%uint64(n-1)};for i:=0;i<n;i++{s:=h.slots[(a+uint64(i)*step)%uint64(n)];if !s.used{return "",false};if s.key==k{return s.value,true}};return "",false}
