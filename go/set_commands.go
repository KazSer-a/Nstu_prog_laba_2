package main

import (
    "bufio"
    "fmt"
    "os"
    "sort"
    "strings"
)

// Обрабатывает стандартный набор команд над множеством.
func setCommands(in *bufio.Reader, out *bufio.Writer) {
    var q int
    if _, err := fmt.Fscan(in, &q); err != nil || q < 0 { fmt.Fprintln(out, "Неверный ввод"); return }
    values := make(l1StringSet)
    for i := 0; i < q; i++ {
        var op, value string
        if _, err := fmt.Fscan(in, &op, &value); err != nil { fmt.Fprintln(out, "Недостаточно данных"); return }
        switch op {
        case "SETADD": values.add(value)
        case "SETDEL": values.remove(value)
        case "SET_AT": if values.contains(value) { fmt.Fprintln(out, "TRUE") } else { fmt.Fprintln(out, "FALSE") }
        default: fmt.Fprintln(out, "Неизвестная команда")
        }
    }
}

// Выполняет одну команду над множеством, сохранённым в файле.
func setFileQuery(fileName, query string, out *bufio.Writer) {
    data, err := os.ReadFile(fileName)
    if err != nil && !os.IsNotExist(err) { fmt.Fprintln(out, "Не удалось прочитать файл"); return }
    values := make(l1StringSet)
    for _, item := range strings.Fields(string(data)) { values.add(item) }
    parts := strings.Fields(query)
    if len(parts) != 2 { fmt.Fprintln(out, "Формат запроса: SETADD|SETDEL|SET_AT <элемент>"); return }
    switch parts[0] {
    case "SETADD": values.add(parts[1])
    case "SETDEL": values.remove(parts[1])
    case "SET_AT": if values.contains(parts[1]) { fmt.Fprintln(out, "TRUE") } else { fmt.Fprintln(out, "FALSE") }; return
    default: fmt.Fprintln(out, "Неизвестная команда"); return
    }
    items := make([]string, 0, len(values))
    for item := range values { items = append(items, item) }
    sort.Strings(items)
    content := strings.Join(items, "\n")
    if len(items) > 0 { content += "\n" }
    if err := os.WriteFile(fileName, []byte(content), 0644); err != nil { fmt.Fprintln(out, "Не удалось сохранить файл"); return }
    fmt.Fprintln(out, "OK")
}
