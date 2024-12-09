#pragma once
#include "sorting/sorter.hpp"


template <typename Type>
class HeapSorter : public ISorter<Type>
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

    void heapify(ISequence<Type>& sequence, size_t n, size_t root)
    {
        size_t largest = root;        
        size_t left = 2 * root + 1;   
        size_t right = 2 * root + 2;  

        if (left < n && comparator(sequence[left], sequence[largest]) == -1)
        {
            largest = left;
        }

        if (right < n && comparator(sequence[right], sequence[largest]) == -1)
        {
            largest = right;
        }

        if (largest != root)
        {
            swap(sequence[root], sequence[largest]);
            heapify(sequence, n, largest);
        }
    }

    void heapSort(ISequence<Type>& sequence)
    {
        size_t n = sequence.getSize();

        for (size_t i = n / 2; i > 0; i--)
        {
            heapify(sequence, n, i - 1);
        }

        for (size_t i = n - 1; i > 0; i--)
        {
            swap(sequence[0], sequence[i]);  
            heapify(sequence, i, 0);             
        }
    }

public:
    HeapSorter(short (*comparator_)(const Type& elem1, const Type& elem2) = defaultComparator)
        : comparator(comparator_) {}

    void sort(ISequence<Type>& sequence) override
    {
        if (sequence.getSize() == 0)
        {
            return;
        }
        heapSort(sequence);
    }
};