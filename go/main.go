package main

import (
    "bufio"
    "fmt"
    "os"
)

// Запускает выбранное задание или команду АТД «Множество» из файла.
func main() {
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()
    if len(os.Args) == 5 && os.Args[1] == "--file" && os.Args[3] == "--query" {
        setFileQuery(os.Args[2], os.Args[4], out)
        return
    }
    if len(os.Args) != 2 {
        fmt.Fprintln(out, "Использование: go run . <1-8> или go run . --file <путь> --query '<команда>'")
        os.Exit(1)
    }
    tasks := map[string]func(*bufio.Reader, *bufio.Writer){
        "1": taskExecutionOrder, "2": setCommands, "3": alienGenome, "4": stressCheck,
        "5": treeRecovery, "6": hashMethods, "7": employeeHierarchy, "8": lruCache,
    }
    task, ok := tasks[os.Args[1]]
    if !ok { fmt.Fprintln(out, "Номер задания должен быть от 1 до 8"); os.Exit(1) }
    task(bufio.NewReader(os.Stdin), out)
}
