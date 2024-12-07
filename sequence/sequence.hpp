#pragma  once
#include <stdexcept>
#include "pointer/unique_ptr.hpp"


template <class Type>
class Sequence
{
public:
    virtual Type& getFirst() = 0;

    virtual Type& getLast() = 0;

    virtual Type& get(size_t index) = 0;

    virtual const Type& getFirst() const = 0;

    virtual const Type& getLast() const = 0;

    virtual const Type& get(size_t index) const = 0;

    virtual size_t getSize() const = 0;

    virtual void set(const Type& value, size_t index) = 0;

    virtual void prepend(const Type& item) = 0;

    virtual void append(const Type& item) = 0;

    virtual void insertAt(const Type& item, size_t index) = 0;

    virtual void removeFirst() = 0;

    virtual void removeLast() = 0;

    virtual void erase(size_t index) = 0;

    virtual ~Sequence() = default;
};