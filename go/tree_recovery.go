package main

import (
    "bufio"
    "fmt"
    "strconv"
    "strings"
)

// Находит две вершины, нарушающие порядок симметричного обхода.
func findSwapped(root *l1TreeNode) (*l1TreeNode, *l1TreeNode) {
    stack := make([]*l1TreeNode, 0)
    current := root
    var previous, first, second *l1TreeNode
    for current != nil || len(stack) > 0 {
        for current != nil { stack = append(stack, current); current = current.left }
        current = stack[len(stack)-1]; stack = stack[:len(stack)-1]
        if previous != nil && previous.key > current.key { if first == nil { first = previous }; second = current }
        previous = current; current = current.right
    }
    return first, second
}

// Проверяет, что восстановленное дерево удовлетворяет порядку BST.
func validSearchTree(root *l1TreeNode) bool {
    stack := make([]*l1TreeNode, 0); current := root; var previous int64; hasPrevious := false
    for current != nil || len(stack) > 0 {
        for current != nil { stack = append(stack, current); current = current.left }
        current = stack[len(stack)-1]; stack = stack[:len(stack)-1]
        if hasPrevious && previous > current.key { return false }
        previous, hasPrevious, current = current.key, true, current.right
    }
    return true
}

// Строит дерево по уровневой записи с маркером отсутствующего узла.
func buildLevelTree(tokens []string) (*l1TreeNode, bool) {
    if len(tokens) == 0 || tokens[0] == "#" { return nil, false }
    rootValue, err := strconv.ParseInt(tokens[0], 10, 64); if err != nil { return nil, false }
    root := &l1TreeNode{key: rootValue}; nodes := []*l1TreeNode{root}; pos := 1
    for i := 0; i < len(nodes) && pos < len(tokens); i++ {
        if tokens[pos] != "#" { value, e := strconv.ParseInt(tokens[pos], 10, 64); if e != nil { return root, false }; nodes[i].left = &l1TreeNode{key:value}; nodes = append(nodes, nodes[i].left) }; pos++
        if pos < len(tokens) { if tokens[pos] != "#" { value, e := strconv.ParseInt(tokens[pos], 10, 64); if e != nil { return root, false }; nodes[i].right = &l1TreeNode{key:value}; nodes = append(nodes, nodes[i].right) }; pos++ }
    }
    return root, pos == len(tokens)
}

// Сериализует дерево в уровневую запись.
func serializeLevelTree(root *l1TreeNode) string {
    queue := []*l1TreeNode{root}; result := make([]string, 0)
    for len(queue) > 0 { node := queue[0]; queue = queue[1:]; if node == nil { result = append(result, "#"); continue }; result = append(result, strconv.FormatInt(node.key, 10)); queue = append(queue, node.left, node.right) }
    for len(result) > 0 && result[len(result)-1] == "#" { result = result[:len(result)-1] }
    return strings.Join(result, " ")
}

// Восстанавливает значения двух перепутанных узлов BST без изменения связей.
func treeRecovery(in *bufio.Reader, out *bufio.Writer) {
    line, err := in.ReadString('\n'); if err != nil && len(line) == 0 { fmt.Fprintln(out, "Неверный ввод"); return }
    tokens := strings.Fields(line); if len(tokens) == 0 || tokens[0] == "#" { fmt.Fprintln(out, "Пустое дерево"); return }
    root, parsed := buildLevelTree(tokens); if !parsed { fmt.Fprintln(out, "Неверное представление дерева"); return }
    first, second := findSwapped(root); if first == nil || second == nil { fmt.Fprintln(out, "Не найдены два перепутанных узла"); return }
    first.key, second.key = second.key, first.key
    if !validSearchTree(root) { first.key, second.key = second.key, first.key; fmt.Fprintln(out, "Не удалось восстановить дерево"); return }
    fmt.Fprintln(out, serializeLevelTree(root))
}
