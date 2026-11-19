package main

import (
    "bufio"
    "fmt"
)

// Считает пары первого генома, присутствующие во втором геноме.
func alienGenome(in *bufio.Reader, out *bufio.Writer) {
    var first, second string
    if _, err := fmt.Fscan(in, &first, &second); err != nil { fmt.Fprintln(out, "Неверный ввод"); return }
    pairs := make(l1StringSet)
    for i := 1; i < len(second); i++ { pairs.add(second[i-1:i+1]) }
    answer := 0
    for i := 1; i < len(first); i++ { if pairs.contains(first[i-1:i+1]) { answer++ } }
    fmt.Fprintln(out, answer)
}
