package main

// Узел стека строк из лабораторной работы №1.
type l1StackNode struct { value string; next *l1StackNode }

// Стек строк с операциями добавления и извлечения.
type l1Stack struct { top *l1StackNode }

// Добавляет элемент на вершину стека.
func (s *l1Stack) push(value string) { s.top = &l1StackNode{value: value, next: s.top} }

// Извлекает элемент с вершины стека.
func (s *l1Stack) pop() (string, bool) { if s.top == nil { return "", false }; value := s.top.value; s.top = s.top.next; return value, true }

// Динамический массив строк из лабораторной работы №1.
type l1Array struct { data []string }

// Добавляет строку в конец массива.
func (a *l1Array) pushBack(value string) { a.data = append(a.data, value) }

// Узел двоичного дерева поиска из лабораторной работы №1.
type l1TreeNode struct { key int64; left, right *l1TreeNode }

// Множество строк с ожидаемыми O(1) операциями.
type l1StringSet map[string]struct{}

// Добавляет элемент во множество.
func (s l1StringSet) add(value string) { s[value] = struct{}{} }

// Удаляет элемент из множества.
func (s l1StringSet) remove(value string) { delete(s, value) }

// Проверяет наличие элемента во множестве.
func (s l1StringSet) contains(value string) bool { _, ok := s[value]; return ok }

// Узел двусвязного списка из лабораторной работы №1.
type l1DNode struct { value string; next, prev *l1DNode }

// Двусвязный список с перемещением узлов за O(1).
type l1DList struct { head, tail *l1DNode }

// Добавляет узел в начало списка.
func (l *l1DList) pushFront(value string) *l1DNode { n := &l1DNode{value: value, next: l.head}; if l.head != nil { l.head.prev = n } else { l.tail = n }; l.head = n; return n }

// Удаляет заданный узел списка.
func (l *l1DList) erase(n *l1DNode) { if n == nil { return }; if n.prev != nil { n.prev.next = n.next } else { l.head = n.next }; if n.next != nil { n.next.prev = n.prev } else { l.tail = n.prev }; n.next, n.prev = nil, nil }
