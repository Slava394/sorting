#pragma once
#include "sorting/sorter.hpp"


template <typename Type> 
class QuickSorter : public ISorter<Type>
{
private:
    short (*comparator)(const Type& elem1, const Type& elem2);

    void swap(Type& elem1, Type& elem2)
    {
        if (comparator(elem1, elem2) != 0)
        {
            Type temp = elem1;
            elem1 = elem2;
            elem2 = temp;
        }
    }

    size_t partition(ISequence<Type>& sequence, size_t low, size_t high)
    {
        Type pivot = sequence[(low + high) / 2];

        size_t i = low;
        size_t j = high;

        while (true)
        {
            while (comparator(sequence[i], pivot) == 1)
            {
                i++;
            }

            while (comparator(sequence[j], pivot) == -1)
            {
                j--;
            }

            if (i >= j)
            {
                return j;
            }

            swap(sequence[i++], sequence[j--]);
        }
    }

    void quickSort(ISequence<Type>& sequence, size_t low, size_t high)
    {
        if (low < high)
        {
            size_t k = partition(sequence, low, high);
            quickSort(sequence, low, k);
            quickSort(sequence, k + 1, high);
        }
    }
public:
    QuickSorter(short (*comparator_)(const Type& elem1, const Type& elem2) = defaultComparator) 
        : comparator(comparator_) {}

    void sort(ISequence<Type>& sequence) override
    {
        if (sequence.getSize() == 0)
        {
            return;
        }
        quickSort(sequence, 0, sequence.getSize() - 1);
    }
};