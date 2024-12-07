#pragma once
#include "sequence/sequence.hpp"
#include "smart_holder/smart_vector.hpp"
#include "pointer/shared_weak_ptr.hpp"
#include "pointer/unique_ptr.hpp"


template <class Type>
class ArraySequence : public Sequence<Type>
{
private:
    SharedPtr<DynamicArray<Type>> holder;
public:
    ArraySequence() : holder(new LinkedArray<Type>()) {}

    ArraySequence(const Type* items, size_t count) : holder(new LinkedArray<Type>(items, count)) {}

    ArraySequence(const ArraySequence<Type>& otherArraySequence) : holder(new LinkedArray<Type>(*otherArraySequence.holder)) {}

    ArraySequence(ArraySequence<Type>&& otherArraySequence) noexcept
    {
        holder = otherArraySequence.holder;
        otherArraySequence.holder = nullptr;
    }

    Type& operator[](size_t index)
    {
        return holder->get(index);
    }

    const Type& operator[](size_t index) const
    {
        return holder->get(index);
    }

    void operator+=(ArraySequence<Type>& otherArraySequence)
    {
        concat(otherArraySequence);
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
        return holder->getSize();
    }

    void set(const Type& value, size_t index) override
    {
        holder->set(value, index);
    }

    void prepend(const Type& item) override
    {
        holder->prepend(item);
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
        holder->removeFirst();
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