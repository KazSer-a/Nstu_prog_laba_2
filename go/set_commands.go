package main
import("bufio";"fmt")
// Обрабатывает команды SETADD, SETDEL и SET_AT.
func setCommands(in *bufio.Reader,out *bufio.Writer){var q int;if _,e:=fmt.Fscan(in,&q);e!=nil||q<0{fmt.Fprintln(out,"Неверный ввод");return};s:=map[string]bool{};for i:=0;i<q;i++{var op,x string;fmt.Fscan(in,&op,&x);switch op{case "SETADD":s[x]=true;case "SETDEL":delete(s,x);case "SET_AT":if s[x]{fmt.Fprintln(out,"TRUE")}else{fmt.Fprintln(out,"FALSE")};default:fmt.Fprintln(out,"Неизвестная команда")}}}
