package main
import("bufio";"fmt";"time")
type openHash struct{keys []int64;used []bool;double bool}
// Создаёт таблицу выбранного метода хеширования.
func newOpenHash(n int,d bool)*openHash{return &openHash{keys:make([]int64,n),used:make([]bool,n),double:d}}
// Вставляет ключ открытой адресацией.
func(h *openHash)insert(x int64)bool{n:=len(h.keys);a:=x%int64(n);if a<0{a+=int64(n)};s:=int64(1);if h.double{s=1+(x%int64(n-1)+int64(n-1))%int64(n-1)};for i:=0;i<n;i++{p:=(a+int64(i)*s)%int64(n);if !h.used[p]{h.used[p]=true;h.keys[p]=x;return true};if h.keys[p]==x{return true}};return false}
// Проверяет размер таблицы и сравнивает время двух методов.
func hashMethods(in *bufio.Reader,out *bufio.Writer){var n,cap int;if _,e:=fmt.Fscan(in,&n,&cap);e!=nil||n<0||cap<3{fmt.Fprintln(out,"Формат: N простая_ёмкость, затем N ключей");return};if !isPrime(cap){fmt.Fprintln(out,"Размер таблицы должен быть простым числом");return};v:=make([]int64,n);for i:=range v{fmt.Fscan(in,&v[i])};for _,d:=range []bool{false,true}{h:=newOpenHash(cap,d);ok:=0;start:=time.Now();for _,x:=range v{if h.insert(x){ok++}};name:="Линейное апробирование";if d{name="Двойное хеширование"};fmt.Fprintf(out,"%s: вставлено %d/%d, время %s\n",name,ok,n,time.Since(start))}}
