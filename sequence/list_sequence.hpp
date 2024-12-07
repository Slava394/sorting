#pragma once
#include "sequence/sequence.hpp"
#include "smart_holder/smart_linked_list.hpp"
#include "pointer/shared_weak_ptr.hpp"
#include "pointer/unique_ptr.hpp"


template <class Type>
class ListSequence : public Sequence<Type>
{
private:
    LinkedList<Type>* holder;
public:
    ListSequence() : holder(new LinkedList<Type>()) {}

    ListSequence(const Type* items, size_t count) : holder(new LinkedList<Type>(items, count)) {}

    ListSequence(const ListSequence<Type>& otherListSequence) : holder(new LinkedList<Type>(*otherListSequence.holder)) {}

    ListSequence(ListSequence<Type>&& otherListSequence) noexcept
    {
        holder = otherListSequence.holder;
        otherListSequence.holder = nullptr;
    }

    ~ListSequence()
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

    void operator+=(ListSequence<Type>& otherListSequence)
    {
        concat(otherListSequence);
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

    void concat(const Sequence<Type>& otherSequence)
    {
        const ListSequence<Type>* otherListSequencePtr = dynamic_cast<const ListSequence<Type>*>(&otherSequence);
        if (otherListSequencePtr) 
        {
            holder->concat(*otherListSequencePtr->holder);
        } 
        else 
        {
            throw std::invalid_argument("Expected a ListSequence.");
        }
    }
};