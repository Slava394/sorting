#include <iostream>
#include <cassert>
#include <complex>
#include "sorting/quick_sorter.hpp"
#include "collection/array_sequence.hpp"


short sorter(std::complex<int>& a, std::complex<int>& b)
{
    if (a.real() > b.real())
    {
        return -1;
    }
    if (a.real() < b.real())
    {
        return 1;
    }
    if (a.imag() > b.imag())
    {
        return -1;
    }
    if (a.imag() < b.imag())
    {
        return 1;
    }
    return 0;
}


int main()
{
    std::complex<int>* arr = new std::complex<int>[6]{{1, 3}, {2, 3}, {4 ,3} ,{5 ,3} ,{6 ,3} ,{1, 1}};
    ArraySequence<std::complex<int>> seq(arr, 6);
    delete[] arr;
    QuickSorter<std::complex<int>> quickSort(sorter);
    quickSort.sort(seq);
    for (size_t i = 0; i < seq.getSize(); ++i)
    {
        std::cout << seq.get(i).real() << " " <<  seq.get(i).imag() << std::endl;
    }
    std::cout << std::endl;
    return 0;
}