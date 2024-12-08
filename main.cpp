#include <iostream>
#include <cassert>
#include "sequence/array_sequence.hpp"
#include "sequence/list_sequence.hpp"

void testSequence() {
    // Тест 1: Базовые операции
    ListSequence<int> sequence;
    sequence.append(10);
    sequence.append(20);
    sequence.prepend(5);
    assert(sequence.getSize() == 3);
    assert(sequence.getFirst() == 5);
    assert(sequence.getLast() == 20);
    assert(sequence.get(1) == 10);

    // Тест 2: Изменение элементов
    sequence.set(15, 1);  // Устанавливаем 15 на место элемента с индексом 1
    assert(sequence.get(1) == 15);

    // Тест 3: Вставка элементов
    sequence.insertAt(12, 1);  // Вставляем 12 между 5 и 15
    assert(sequence.getSize() == 4);
    assert(sequence.get(1) == 12);
    assert(sequence.get(2) == 15);

    // Тест 4: Удаление элементов
    sequence.erase(1);  // Удаляем элемент с индексом 1 (значение 12)
    assert(sequence.getSize() == 3);
    assert(sequence.get(1) == 15);
    sequence.removeFirst();  // Удаляем первый элемент
    assert(sequence.getFirst() == 15);
    sequence.removeLast();   // Удаляем последний элемент
    assert(sequence.getSize() == 1);
    assert(sequence.getFirst() == 15);

    // Тест 5: Исключения
    try {
        sequence.get(10);  // Некорректный индекс
        assert(false);     // Должно выбросить исключение
    } catch (const std::out_of_range&) {
        std::cout << "Caught exception: get with invalid index.\n";
    }

    try {
        sequence.erase(5);  // Некорректный индекс
        assert(false);      // Должно выбросить исключение
    } catch (const std::out_of_range&) {
        std::cout << "Caught exception: erase with invalid index.\n";
    }

    // Тест 6: Пустая последовательность
    sequence.removeFirst();
    assert(sequence.getSize() == 0);
    try {
        sequence.getFirst();
        assert(false);  // Должно выбросить исключение
    } catch (const std::invalid_argument&) {
        std::cout << "Caught exception: getFirst on empty sequence.\n";
    }

    std::cout << "All tests passed!\n";
}

void testArraySequence() {
    // Тест 1: Базовые операции
    ArraySequence<int> sequence;
    sequence.append(10);
    sequence.append(20);
    sequence.prepend(5);
    assert(sequence.getSize() == 3);
    assert(sequence.getFirst() == 5);
    assert(sequence.getLast() == 20);
    assert(sequence.get(1) == 10);

    // Тест 2: Изменение элементов
    sequence.set(15, 1);  // Устанавливаем 15 на место элемента с индексом 1
    assert(sequence.get(1) == 15);

    // Тест 3: Вставка элементов
    sequence.insertAt(12, 1);  // Вставляем 12 между 5 и 15
    assert(sequence.getSize() == 4);
    assert(sequence.get(1) == 12);
    assert(sequence.get(2) == 15);

    // Тест 4: Удаление элементов
    sequence.erase(1);  // Удаляем элемент с индексом 1 (значение 12)
    assert(sequence.getSize() == 3);
    assert(sequence.get(1) == 15);
    sequence.removeFirst();  // Удаляем первый элемент
    assert(sequence.getFirst() == 15);
    sequence.removeLast();   // Удаляем последний элемент
    assert(sequence.getSize() == 1);
    assert(sequence.getFirst() == 15);

    // Тест 5: Исключения
    try {
        sequence.get(10);  // Некорректный индекс
        assert(false);     // Должно выбросить исключение
    } catch (const std::out_of_range&) {
        std::cout << "Caught exception: get with invalid index.\n";
    }

    try {
        sequence.erase(5);  // Некорректный индекс
        assert(false);      // Должно выбросить исключение
    } catch (const std::out_of_range&) {
        std::cout << "Caught exception: erase with invalid index.\n";
    }

    // Тест 6: Пустая последовательность
    sequence.removeFirst();
    assert(sequence.getSize() == 0);
    try {
        sequence.getFirst();
        assert(false);  // Должно выбросить исключение
    } catch (const std::out_of_range&) {
        std::cout << "Caught exception: getFirst on empty sequence.\n";
    }

    std::cout << "All ArraySequence tests passed!\n";
}

int main() {
    testArraySequence();
    testSequence();
    return 0;
}