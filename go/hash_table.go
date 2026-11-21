package main

type slotState uint8

const (
    emptySlot slotState = iota
    occupiedSlot
    deletedSlot
)

type hashSlot[K comparable, V any] struct {
    key   K
    value V
    state slotState
}

type hashTable[K comparable, V any] struct {
    slots   l1Array[hashSlot[K, V]]
    hash    func(K, int) int
    double  bool
    entries int
    used    int
}

func isPrime(n int) bool {
    if n < 2 {
        return false
    }
    for d := 2; d <= n/d; d++ {
        if n%d == 0 {
            return false
        }
    }
    return true
}

func nextPrime(size int) int {
    for !isPrime(size) {
        size++
    }
    return size
}

func newHashTable[K comparable, V any](capacity int, double bool, hash func(K, int) int) *hashTable[K, V] {
    return &hashTable[K, V]{
        slots: l1Array[hashSlot[K, V]]{data: make([]hashSlot[K, V], capacity), size: capacity},
        hash: hash, double: double,
    }
}

func intHash(value int64, modulus int) int {
    remainder := value % int64(modulus)
    if remainder < 0 {
        remainder += int64(modulus)
    }
    return int(remainder)
}

func stringHash(value string, modulus int) int {
    // FNV-1a over the bytes of the key.
    hash := uint64(14695981039346656037)
    for i := 0; i < len(value); i++ {
        hash = (hash ^ uint64(value[i])) * 1099511628211
    }
    return int(hash % uint64(modulus))
}

// locate returns an existing key or the first slot available for insertion.
func (h *hashTable[K, V]) locate(key K) (position, probes int, found bool) {
    capacity := h.slots.size
    position = h.hash(key, capacity)
    step := 1
    if h.double {
        step += h.hash(key, capacity-1)
    }
    firstDeleted := capacity
    for probes = 1; probes <= capacity; probes++ {
        slot := h.slots.data[position]
        switch {
        case slot.state == emptySlot:
            if firstDeleted != capacity {
                position = firstDeleted
            }
            return position, probes, false
        case slot.state == occupiedSlot && slot.key == key:
            return position, probes, true
        case slot.state == deletedSlot && firstDeleted == capacity:
            firstDeleted = position
        }
        position = (position + step) % capacity
    }
    return firstDeleted, capacity, false
}

func (h *hashTable[K, V]) insert(key K, value V) int {
    position, probes, found := h.locate(key)
    if position == h.slots.size {
        return probes
    }
    slot := &h.slots.data[position]
    if !found {
        h.entries++
        if slot.state == emptySlot {
            h.used++
        }
    }
    *slot = hashSlot[K, V]{key: key, value: value, state: occupiedSlot}
    return probes
}

func (h *hashTable[K, V]) get(key K) (V, bool) {
    position, _, found := h.locate(key)
    if found {
        return h.slots.data[position].value, true
    }
    var zero V
    return zero, false
}

func (h *hashTable[K, V]) remove(key K) {
    position, _, found := h.locate(key)
    if found {
        h.slots.data[position] = hashSlot[K, V]{state: deletedSlot}
        h.entries--
    }
}

func (h *hashTable[K, V]) forEach(visit func(K, V)) {
    for _, slot := range h.slots.data {
        if slot.state == occupiedSlot {
            visit(slot.key, slot.value)
        }
    }
}

func (h *hashTable[K, V]) insertGrowing(key K, value V) {
    capacity := h.slots.size
    if h.used >= capacity/2 {
        newCapacity := capacity
        if h.entries > capacity/4 {
            newCapacity = nextPrime(capacity * 2)
        }
        rebuilt := newHashTable[K, V](newCapacity, h.double, h.hash)
        h.forEach(func(key K, value V) { rebuilt.insert(key, value) })
        *h = *rebuilt
    }
    h.insert(key, value)
}

type stringSet struct {
    *hashTable[string, bool]
}

func newStringSet() stringSet {
    return stringSet{newHashTable[string, bool](11, true, stringHash)}
}

func (s stringSet) add(value string) { s.insertGrowing(value, true) }

func (s stringSet) contains(value string) bool {
    _, found := s.get(value)
    return found
}
