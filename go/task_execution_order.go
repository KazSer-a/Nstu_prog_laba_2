package main

import (
    "bufio"
    "fmt"
    "strconv"
)

// Проверяет возможность завершить все задачи топологической сортировкой со стеком.
func taskExecutionOrder(in *bufio.Reader, out *bufio.Writer) {
    var n, m int
    if _, err := fmt.Fscan(in, &n, &m); err != nil || n < 0 || m < 0 { fmt.Fprintln(out, "Неверный ввод"); return }
    ids := make(map[string]int)
    graph := make([][]int, 0)
    indegree := make([]int, 0)
    getID := func(name string) int {
        if id, ok := ids[name]; ok { return id }
        id := len(ids); ids[name] = id; graph = append(graph, nil); indegree = append(indegree, 0); return id
    }
    for i := 0; i < n; i++ { var name string; if _, err := fmt.Fscan(in, &name); err != nil { fmt.Fprintln(out, "Недостаточно имён задач"); return }; getID(name) }
    for i := 0; i < m; i++ {
        var task, prerequisite string
        if _, err := fmt.Fscan(in, &task, &prerequisite); err != nil { fmt.Fprintln(out, "Недостаточно зависимостей"); return }
        from, to := getID(prerequisite), getID(task); graph[from] = append(graph[from], to); indegree[to]++
    }
    var stack l1Stack
    for id, degree := range indegree { if degree == 0 { stack.push(strconv.Itoa(id)) } }
    completed := 0
    for {
        item, ok := stack.pop(); if !ok { break }
        vertex, _ := strconv.Atoi(item); completed++
        for _, next := range graph[vertex] { indegree[next]--; if indegree[next] == 0 { stack.push(strconv.Itoa(next)) } }
    }
    if completed == len(indegree) { fmt.Fprintln(out, "Возможно") } else { fmt.Fprintln(out, "Невозможно") }
}
