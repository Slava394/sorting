#include <iostream>
#include <cassert>
#include "smart_holder/smart_vector.hpp"

void testDynamicArray()
{
    // Тест 1: Конструктор по умолчанию
    {
        DynamicArray<int> array;
        assert(array.getSize() == 0);
    }

    // Тест 2: Конструктор с длиной
    {
        DynamicArray<int> array(5);
        assert(array.getSize() == 5);
        for (size_t i = 0; i < array.getSize(); ++i)
        {
            array.set(i * 2, i);
        }
        for (size_t i = 0; i < array.getSize(); ++i)
        {
            assert(array.get(i) == static_cast<int>(i * 2));
        }
    }

    // Тест 3: Добавление элемента (append)
    {
        DynamicArray<int> array;
        array.append(10);
        assert(array.getSize() == 1);
        assert(array.get(0) == 10);
    }

    // Тест 4: Вставка элемента (insertAt)
    {
        DynamicArray<int> array;
        array.append(1);
        array.append(3);
        array.insertAt(2, 1);
        assert(array.getSize() == 3);
        assert(array.get(0) == 1);
        assert(array.get(1) == 2);
        assert(array.get(2) == 3);
    }

    // Тест 5: Удаление элемента (erase)
    {
        DynamicArray<int> array;
        array.append(1);
        array.append(2);
        array.append(3);
        array.erase(1);
        assert(array.getSize() == 2);
        assert(array.get(0) == 1);
        assert(array.get(1) == 3);
    }

    // Тест 6: Получение первого и последнего элементов
    {
        DynamicArray<int> array;
        array.append(5);
        array.append(10);
        assert(array.getFirst() == 5);
        assert(array.getLast() == 10);
    }

    // Тест 7: Удаление последнего элемента (removeLast)
    {
        DynamicArray<int> array;
        array.append(42);
        array.removeLast();
        assert(array.getSize() == 0);
    }

    // Тест 8: Копирование (copy constructor)
    {
        DynamicArray<int> array;
        array.append(1);
        array.append(2);
        DynamicArray<int> copy(array);
        assert(copy.getSize() == 2);
        assert(copy.get(0) == 1);
        assert(copy.get(1) == 2);
    }

    // Тест 9: Перемещение (move constructor)
    {
        DynamicArray<int> array;
        array.append(1);
        array.append(2);
        DynamicArray<int> moved(std::move(array));
        assert(moved.getSize() == 2);
        assert(moved.get(0) == 1);
        assert(moved.get(1) == 2);
        assert(array.getSize() == 0); // Исходный массив должен быть пуст
    }

    // Тест 10: Исключения
    {
        DynamicArray<int> array;
        try
        {
            array.getFirst();
            assert(false); // Должно выбросить исключение
        }
        catch (const std::logic_error& e)
        {
            assert(std::string(e.what()) == "Index out of range.");
        }

        try
        {
            array.erase(0);
            assert(false); // Должно выбросить исключение
        }
        catch (const std::out_of_range& e)
        {
            assert(std::string(e.what()) == "Index out of range.");
        }
    }

    std::cout << "All tests passed!" << std::endl;
}

int main()
{
    testDynamicArray();
    return 0;
}