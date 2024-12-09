#include <iostream>
#include <cassert>
#include <complex>
#include "sorting/quick_sorter.hpp"
#include "sorting/shell_sorter.hpp"
#include "sorting/heap_sorter.hpp"
#include "collection/array_sequence.hpp"
#include "collection/list_sequence.hpp"


short sorter(const int& a, const int& b)
{
    if (a > b)
    {
        return -1;
    }
    if (a < b)
    {
        return 1;
    }
    return 0;
}


int main()
{
    int* arr = new int[7]{8, 3, 3, 2, 2, 6, 1};
    ListSequence<int> seq(arr, 7);
    delete[] arr;
    HeapSorter<int> shellSort(sorter);
    shellSort.sort(seq);
    for (size_t i = 0; i < seq.getSize(); ++i)
    {
        std::cout << seq.get(i) << " ";
    }
    std::cout << std::endl;
    return 0;
}