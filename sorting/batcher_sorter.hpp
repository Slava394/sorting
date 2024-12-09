#pragma once
#include "sorting/sorter.hpp"


template <typename Type>
class BatcherSorter : public ISorter<Type>
{
private:
    short (*comparator)(const Type& elem1, const Type& elem2);

    void swapIfNeeded(Type& a, Type& b, bool ascending)
    {
        if ((ascending && comparator(a, b) == -1) || (!ascending && comparator(a, b) == 1))
        {
            std::swap(a, b);
        }
    }

    void bitonicMerge(ISequence<Type>& sequence, size_t low, size_t count, bool ascending)
    {
        if (count > 1)
        {
            size_t mid = count / 2;

            for (size_t i = low; i < low + mid; i++)
            {
                swapIfNeeded(sequence[i], sequence[i + mid], ascending);
            }

            bitonicMerge(sequence, low, mid, ascending);
            bitonicMerge(sequence, low + mid, mid, ascending);
        }
    }

    void bitonicSort(ISequence<Type>& sequence, size_t low, size_t count, bool ascending)
    {
        if (count > 1)
        {
            size_t mid = count / 2;
            bitonicSort(sequence, low, mid, true);       
            bitonicSort(sequence, low + mid, mid, false); 
            bitonicMerge(sequence, low, count, ascending); 
        }
    }
public:
    BatcherSorter(short (*comparator_)(const Type& elem1, const Type& elem2) = defaultComparator)
        : comparator(comparator_) {}

    void sort(ISequence<Type>& sequence) override
    {
        size_t n = sequence.getSize();
        
        if (n == 0)
        {
            return;
        }

        size_t powerOfTwo = 1;
        
        while (powerOfTwo < n)
        {
            powerOfTwo *= 2;
        }

        if (powerOfTwo != n)
        {
            throw std::invalid_argument("Batcher's sort requires a sequence of length that is a power of two.");
        }

        bitonicSort(sequence, 0, n, true); 
    }
};