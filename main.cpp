#include <iostream>
#include <cassert>
#include "sorting/quick_sorter.hpp"
#include "collection/array_sequence.hpp"


int main()
{
    int* arr = new int[12]{1, 3, 2, 3, 4 ,3 ,5 ,3 ,6 ,3 ,7, 3};
    ArraySequence<int> seq(arr, 12);
    delete[] arr;
    QuickSorter<int> quickSort;
    quickSort.sort(seq);
    for (size_t i = 0; i < seq.getSize(); ++i)
    {
        std::cout << seq.get(i) << " ";
    }
    std::cout << std::endl;
    return 0;
}