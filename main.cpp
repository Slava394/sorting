#include <cassert>
#include <iostream>
#include "sequence/array_sequence.hpp"

void testArraySequence() {
    // Тесты на создание пустого массива
    ArraySequence<int> emptySeq;
    assert(emptySeq.getSize() == 0);

    // Тесты на создание из массива элементов
    int items[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(items, 5);
    assert(seq.getSize() == 5);
    assert(seq.getFirst() == 1);
    assert(seq.getLast() == 5);

    // Тесты на добавление элементов
    seq.append(6);
    assert(seq.getSize() == 6);
    assert(seq.getLast() == 6);

    seq.prepend(0);
    assert(seq.getSize() == 7);
    assert(seq.getFirst() == 0);

    seq.insertAt(100, 3);
    assert(seq.getSize() == 8);
    assert(seq.get(3) == 100);

    // Тесты на изменение элементов
    seq.set(42, 0);
    assert(seq.getFirst() == 42);

    seq.set(99, seq.getSize() - 1);
    assert(seq.getLast() == 99);

    // Тесты на удаление элементов
    seq.removeFirst();
    assert(seq.getFirst() == 1);

    seq.removeLast();
    assert(seq.getLast() == 5);

    seq.erase(2);
    assert(seq.get(2) != 100);

    // Тесты на копирование
    ArraySequence<int> copySeq(seq);
    assert(copySeq.getSize() == seq.getSize());
    for (size_t i = 0; i < copySeq.getSize(); ++i) {
        assert(copySeq[i] == seq[i]);
    }

    // Тесты на перемещение
    ArraySequence<int> movedSeq(std::move(seq));
    assert(movedSeq.getSize() == copySeq.getSize());
    for (size_t i = 0; i < movedSeq.getSize(); ++i) {
        assert(movedSeq[i] == copySeq[i]);
    }
    assert(seq.getSize() == 0);  // Оригинальный объект seq должен быть пуст

    // Тесты на работу с const ArraySequence
    const ArraySequence<int>& constSeq = copySeq;
    assert(constSeq.getFirst() == copySeq.getFirst());
    assert(constSeq.getLast() == copySeq.getLast());
    assert(constSeq.get(1) == copySeq.get(1));
}

int main() {
    testArraySequence();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}