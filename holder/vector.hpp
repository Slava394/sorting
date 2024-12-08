#pragma once
#include <stdexcept>
#include "pointer/shared_weak_ptr.hpp"
#include "pointer/unique_array.hpp"


template <class Type>
class Vector
{
private:
    UniqueArray<Type> data;
    size_t allocatedMemory;
    size_t size;

    void checkIndexRange(size_t index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range.");
        }
    }

    void reserve(size_t newAllocatedMemory)
    {
        if (newAllocatedMemory < size)
        {
            throw std::invalid_argument("Can`t allocate memory less than the current value.");
        }
        UniqueArray<Type> newData;
        if (newAllocatedMemory > 0) 
        {
            newData = UniqueArray<Type>(new Type[newAllocatedMemory]);
            for (size_t index = 0; index < size; ++index)
            {
                newData[index] = data[index];
            }
        }
        data = std::move(newData);
        allocatedMemory = newAllocatedMemory;
    }

    void resize(size_t newSize)
    {
        UniqueArray<Type> newData;
        if (newSize > 0)
        {
            newData = UniqueArray<Type>(new Type[newSize]);
            for (size_t index = 0; index < std::min(size, newSize); ++index)
            {
                newData[index] = data[index];
            }
        }
        data = std::move(newData);
        allocatedMemory = newSize;
        size = newSize;
    }

    void grow()
    {
        if (allocatedMemory == 0)
        {
            reserve(2);
        }
        else
        {
            reserve(allocatedMemory * 2);
        }
    }
public:
    explicit Vector(size_t length = 0) : data(nullptr), allocatedMemory(length), size(length)
    {
        data = UniqueArray<Type>(new Type[length]);
    }

    Vector(const Type* items, size_t count) : data(nullptr), allocatedMemory(count), size(count)
    {
        data = UniqueArray<Type>(new Type[count]);
        for (size_t index = 0; index < count; ++index)
        {
            data[index] = items[index];
        }
    }

    Vector(const Vector<Type>& otherArray) 
        : data(nullptr),
          allocatedMemory(otherArray.allocatedMemory),
          size(otherArray.size)
    {
        if (otherArray.allocatedMemory > 0)
        {
            data = UniqueArray<Type>(new Type[otherArray.allocatedMemory]);
            for (size_t index = 0; index < otherArray.getSize(); ++index)
            {
                data[index] = otherArray.get(index);
            }
        }
    }

    Vector(Vector<Type>&& otherArray) noexcept 
        : data(std::move(otherArray.data)),
          allocatedMemory(otherArray.allocatedMemory),
          size(otherArray.size)
    {
        otherArray.data = nullptr;
        otherArray.allocatedMemory = 0;
        otherArray.size = 0;
    }

    Vector<Type>& operator=(const Vector<Type>& otherArray)
    {
        if (this != &otherArray)
        {
            UniqueArray<Type> newData;
            if (otherArray.allocatedMemory > 0)
            {
                newData = UniqueArray<Type>(new Type[otherArray.allocatedMemory]);
                for (size_t index = 0; index < otherArray.size; ++index)
                {
                    newData[index] = otherArray.data[index];
                }
            }
            data = std::move(newData);
            allocatedMemory = otherArray.allocatedMemory;
            size = otherArray.size;
        }
        return *this;
    }

    Vector<Type>& operator=(Vector<Type>&& otherArray) noexcept
    {
        if (this != &otherArray)
        {
            data = std::move(otherArray.data);
            allocatedMemory = otherArray.allocatedMemory;
            size = otherArray.size;
            otherArray.data = nullptr;
            otherArray.allocatedMemory = 0;
            otherArray.size = 0;
        }
        return *this;
    }

    Type& operator[](size_t index)
    {
        return get(index);
    }

    const Type& operator[](size_t index) const
    {
        return get(index);
    }

    ~Vector()
    {
        clear();
    }

    Type& getFirst() 
    {
        checkIndexRange(0);
        return data[0];
    }

    Type& getLast() 
    {
        checkIndexRange(size - 1);
        return data[size - 1];
    }

    Type& get(size_t index) 
    {
        checkIndexRange(index);
        return data[index];
    }

    const Type& getFirst() const 
    {
        checkIndexRange(0);
        return data[0];
    }

    const Type& getLast() const
    {
        checkIndexRange(0);
        return data[size - 1];
    }

    const Type& get(size_t index) const
    {
        checkIndexRange(size - 1);
        return data[index];
    }

    size_t getSize() const 
    {
        return size;
    }

    void set(const Type& value, size_t index)
    {
        checkIndexRange(index);
        data[index] = value;
    }

    void insertAt(const Type& value, size_t index)
    {
        if (index > size)
        {
            throw std::out_of_range("Index out of range.");
        }
        if (size == allocatedMemory)
        {
            grow();
        }
        for (size_t backIndex = size; index < backIndex; --backIndex)
        {
            data[backIndex] = data[backIndex - 1];
        }
        data[index] = value;
        size++;
    }

    void append(const Type& value)
    {
        if (size == allocatedMemory)
        {
            grow();
        }
        data[size++] = value;
    }

    void erase(size_t index)
    {
        checkIndexRange(index);
        for (size_t newIndex = index; newIndex + 1 < size; ++newIndex)
        {
            data[newIndex] = data[newIndex + 1];
        }
        size--;
    }

    void removeLast()
    {
        if (size == 0)
        {
            throw std::logic_error("Can`t remove last element from an empty array.");
        }
        else if (size > 0)
        {
            size--;
        }
    }

    void clear()
    {
        data = nullptr;
        allocatedMemory = 0;
        size = 0;
    }
};