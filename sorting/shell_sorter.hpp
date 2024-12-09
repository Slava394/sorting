#pragma once
#include "sorting/sorter.hpp"


template <typename Type>
class ShellSorter : public ISorter<Type>
{
private:
    short (*comparator)(const Type& elem1, const Type& elem2);
    size_t gap;

    void shellSort(ISequence<Type>& sequence)
    {
        size_t n = sequence.getSize();
        size_t step = (gap == 0 || gap > n) ? n / 2 : gap;

        for (; step > 0; step /= 2)
        {
            for (size_t i = step; i < n; i++)
            {
                Type temp = sequence[i];
                size_t j = i;

                while (j >= step && comparator(sequence[j - step], temp) == -1)
                {
                    sequence[j] = sequence[j - step];
                    j -= step;
                }

                sequence[j] = temp;
            }
        }
    }
public:
    ShellSorter(short (*comparator_)(const Type& elem1, const Type& elem2) = defaultComparator, size_t gap_ = 0)
        : comparator(comparator_), gap(gap_) {}

    void sort(ISequence<Type>& sequence) override
    {
        if (sequence.getSize() == 0)
        {
            return;
        }
        shellSort(sequence);
    }
};