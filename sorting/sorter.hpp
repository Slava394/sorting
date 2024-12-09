#pragma once
#include "collection/sequence.hpp"


template <typename Type>
class ISorter
{
public:
    virtual void sort(ISequence<Type>& sequence) = 0;
};