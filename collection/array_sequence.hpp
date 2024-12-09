#pragma once
#include "collection/sequence.hpp"
#include "holder/vector.hpp"


template <class Type>
class ArraySequence : public ISequence<Type>
{
private:
    Vector<Type>* holder;
public:
    ArraySequence(size_t size = 0) : holder(new Vector<Type>(size)) {}

    ArraySequence(const Type* items, size_t count) : holder(new Vector<Type>(items, count)) {}

    ArraySequence(const ArraySequence<Type>& otherArraySequence) : holder(new Vector<Type>(*otherArraySequence.holder)) {}

    ArraySequence(ArraySequence<Type>&& otherArraySequence) noexcept
    {
        holder = otherArraySequence.holder;
        otherArraySequence.holder = nullptr;
    }

    ~ArraySequence()
    {
        delete holder;
    }

    Type& operator[](size_t index)
    {
        return holder->get(index);
    }

    const Type& operator[](size_t index) const
    {
        return holder->get(index);
    }

    Type& getFirst() override
    {
        return holder->getFirst();
    }

    Type& getLast() override
    {
        return holder->getLast();
    }

    Type& get(size_t index) override
    {
        return holder->get(index);
    }

    const Type& getFirst() const override
    {
        return holder->getFirst();
    }

    const Type& getLast() const override
    {
        return holder->getLast();
    }

    const Type& get(size_t index) const override
    {
        return holder->get(index);
    }

    size_t getSize() const override
    {
        if (holder == nullptr) 
        {
            return 0;
        }
        return holder->getSize();
    }

    void set(const Type& value, size_t index) override
    {
        holder->set(value, index);
    }

    void prepend(const Type& item) override
    {
        holder->insertAt(item, 0);
    }

    void append(const Type& item) override
    {
        holder->append(item);
    }

    void insertAt(const Type& item, size_t index) override
    {
        holder->insertAt(item, index);
    }

    void removeFirst() override
    {
        holder->erase(0);
    }

    void removeLast() override
    {
        holder->removeLast();
    }

    void erase(size_t index) override
    {
        holder->erase(index);
    }
};