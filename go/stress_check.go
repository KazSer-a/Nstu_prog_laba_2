package main

import (
    "bufio"
    "fmt"
    "strings"
    "unicode"
)

// Нормализует слово и возвращает позицию ударения.
func normalizeWord(word string) (string, int) {
    key := make([]rune, 0, len([]rune(word)))
    stress := -1
    for _, r := range word { if unicode.IsUpper(r) { stress = len(key) }; key = append(key, unicode.ToLower(r)) }
    return string(key), stress
}

// Проверяет ударения во всех словах текстовой строки.
func stressCheck(in *bufio.Reader, out *bufio.Writer) {
    var n int
    if _, err := fmt.Fscan(in, &n); err != nil || n < 0 { fmt.Fprintln(out, "Неверный ввод"); return }
    dictionary := make(map[string]map[int]bool)
    for i := 0; i < n; i++ {
        var word string
        if _, err := fmt.Fscan(in, &word); err != nil { fmt.Fprintln(out, "Недостаточно слов словаря"); return }
        key, position := normalizeWord(word)
        if dictionary[key] == nil { dictionary[key] = make(map[int]bool) }
        dictionary[key][position] = true
    }
    _, _ = in.ReadString('\n')
    line, _ := in.ReadString('\n')
    var words l1Array[string]
    for _, word := range strings.Fields(line) { words.pushBack(word) }
    errors := 0
    for _, word := range words.data[:words.size] {
        key, position := normalizeWord(word)
        count := 0
        for _, r := range word { if unicode.IsUpper(r) { count++ } }
        allowed, known := dictionary[key]
        if !known { if count != 1 { errors++ } } else if count != 1 || !allowed[position] { errors++ }
    }
    fmt.Fprintln(out, errors)
}
