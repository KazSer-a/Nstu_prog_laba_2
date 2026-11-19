package main
import("bufio";"fmt";"os")
// Запускает выбранное лабораторное задание.
func main(){if len(os.Args)!=2{fmt.Println("Использование: go run . <1-8>");os.Exit(1)};tasks:=map[string]func(*bufio.Reader,*bufio.Writer){"1":taskExecutionOrder,"2":setCommands,"3":alienGenome,"4":stressCheck,"5":treeRecovery,"6":hashMethods,"7":employeeHierarchy,"8":lruCache};f,ok:=tasks[os.Args[1]];if !ok{fmt.Println("Использование: go run . <1-8>");os.Exit(1)};in:=bufio.NewReader(os.Stdin);out:=bufio.NewWriter(os.Stdout);defer out.Flush();f(in,out)}
