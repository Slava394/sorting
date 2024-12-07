#include <iostream>
#include <cassert>
#include "sequence/array_sequence.hpp"
#include "sequence/list_sequence.hpp"


void testDynamicArray()
{
    ListSequence<int> seq;
    for (int i = 0; i < 10000000; ++i)
    {
        seq.append(i);
    }
    std::cout << "bruh" << std::endl;
    for (int i = 0; i < 10000000 - 10; ++i)
    {
        seq.removeLast();
    }
    for (int i = 0; i < seq.getSize(); ++i)
    {
        std::cout << seq.get(i) << std::endl;
    }
}

int main()
{
    testDynamicArray();
    return 0;
}