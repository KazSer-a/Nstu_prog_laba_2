package main
import("bufio";"fmt")
// Считает пары первого генома, встречающиеся во втором.
func alienGenome(in *bufio.Reader,out *bufio.Writer){var a,b string;if _,e:=fmt.Fscan(in,&a,&b);e!=nil{fmt.Fprintln(out,"Неверный ввод");return};p:=map[string]bool{};for i:=1;i<len(b);i++{p[b[i-1:i+1]]=true};ans:=0;for i:=1;i<len(a);i++{if p[a[i-1:i+1]]{ans++}};fmt.Fprintln(out,ans)}
