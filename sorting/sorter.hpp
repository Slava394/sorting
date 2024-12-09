#pragma once
#include "collection/sequence.hpp"


template <typename Type>
class ISorter
{
public:
    virtual void sort(ISequence<Type>& sequence) = 0;
};


template <typename Type>
short defaultComparator(const Type& elem1, const Type& elem2)
{
    if (elem1 > elem2)
    {
        return -1;
    }
    if (elem1 < elem2)
    {
        return 1;
    }
    return 0;
}