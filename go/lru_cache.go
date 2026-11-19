package main
import("bufio";"container/list";"fmt")
type cacheEntry struct{key,value int64}
// Выполняет запросы SET и GET с вытеснением LRU.
func lruCache(in *bufio.Reader,out *bufio.Writer){var cap,q int;if _,e:=fmt.Fscan(in,&cap,&q);e!=nil||cap<0||q<0{fmt.Fprintln(out,"Формат: ёмкость количество_запросов");return};order:=list.New();idx:=map[int64]*list.Element{};for i:=0;i<q;i++{var op string;var x,y int64;fmt.Fscan(in,&op,&x);switch op{case "SET":fmt.Fscan(in,&y);if el,ok:=idx[x];ok{el.Value.(*cacheEntry).value=y;order.MoveToFront(el)}else if cap>0{if order.Len()==cap{last:=order.Back();delete(idx,last.Value.(*cacheEntry).key);order.Remove(last)};idx[x]=order.PushFront(&cacheEntry{x,y})};case "GET":if el,ok:=idx[x];ok{order.MoveToFront(el);fmt.Fprint(out,el.Value.(*cacheEntry).value," ")}else{fmt.Fprint(out,"-1 ")};default:fmt.Fprint(out,"Неизвестная команда ")}};fmt.Fprintln(out)}
