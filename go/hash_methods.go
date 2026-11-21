package main

import (
    "bufio"
    "fmt"
    "time"
)

func hashMethods(in *bufio.Reader, out *bufio.Writer) {
    var count, capacity int
    if _, err := fmt.Fscan(in, &count, &capacity); err != nil || count < 0 || capacity < 3 {
        fmt.Fprintln(out, "Формат: количество_ключей простая_ёмкость_таблицы, затем ключи")
        return
    }
    if !isPrime(capacity) {
        fmt.Fprintln(out, "Размер таблицы должен быть простым числом")
        return
    }
    data := make([]int64, count)
    for i := range data {
        if _, err := fmt.Fscan(in, &data[i]); err != nil {
            fmt.Fprintln(out, "Недостаточно ключей")
            return
        }
    }
    for _, method := range []struct {
        name   string
        double bool
    }{{"Линейное пробирование", false}, {"Двойное хеширование", true}} {
        table := newHashTable[int64, bool](capacity, method.double, intHash)
        probes := 0
        start := time.Now()
        for _, value := range data {
            probes += table.insert(value, true)
        }
        elapsed := time.Since(start)
        fmt.Fprintf(out, "%s: вставлено %d/%d, проверено ячеек %d, время %d нс\n",
            method.name, table.entries, count, probes, elapsed.Nanoseconds())
    }
}
