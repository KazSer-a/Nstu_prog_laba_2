package main
import("bufio";"fmt";"strings";"unicode")
// Нормализует слово и определяет позицию ударения.
func normalizeWord(w string)(string,int){r:=[]rune{};p:=-1;for _,c:=range w{if unicode.IsUpper(c){p=len(r)};r=append(r,unicode.ToLower(c))};return string(r),p}
// Проверяет расстановку ударений во всех словах строки.
func stressCheck(in *bufio.Reader,out *bufio.Writer){var n int;if _,e:=fmt.Fscan(in,&n);e!=nil||n<0{fmt.Fprintln(out,"Неверный ввод");return};d:=map[string]map[int]bool{};for i:=0;i<n;i++{var w string;fmt.Fscan(in,&w);k,p:=normalizeWord(w);if d[k]==nil{d[k]=map[int]bool{}};d[k][p]=true};line,_:=in.ReadString('\n');if strings.TrimSpace(line)==""{line,_=in.ReadString('\n')};errors:=0;for _,w:=range strings.Fields(line){k,p:=normalizeWord(w);count:=0;for _,c:=range w{if unicode.IsUpper(c){count++}};valid,known:=d[k];if !known{if count!=1{errors++}}else if count!=1||!valid[p]{errors++}};fmt.Fprintln(out,errors)}
