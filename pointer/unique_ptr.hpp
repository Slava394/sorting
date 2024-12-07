#pragma once
#include <stdexcept>


template<typename Type>
class UniquePtr
{
private:
    Type* dataPtr;

    void release()
    {
        delete dataPtr;
        dataPtr = nullptr;
    }
public:
    explicit UniquePtr(Type* dataPtr_ = nullptr)
        : dataPtr(dataPtr_) {}

    UniquePtr(const UniquePtr<Type>&) = delete;

    UniquePtr(UniquePtr<Type>&& uniquePtr) noexcept
        : dataPtr(uniquePtr.dataPtr)
    {
        uniquePtr.dataPtr = nullptr;
    }

    ~UniquePtr()
    {
        release();
    }

    UniquePtr<Type>& operator=(const UniquePtr<Type>&) = delete;

    UniquePtr<Type>& operator=(UniquePtr<Type>&& uniquePtr) noexcept
    {
        if (dataPtr != uniquePtr.dataPtr)
        {
            release();
            dataPtr = uniquePtr.dataPtr;
            uniquePtr.dataPtr = nullptr;
        }
        return *this;
    }

    bool operator==(const UniquePtr<Type>& uniquePtr) const
    {
        return dataPtr == uniquePtr.dataPtr;
    }

    bool operator!=(const UniquePtr<Type>& uniquePtr) const
    {
        return dataPtr != uniquePtr.dataPtr;
    }

    bool operator==(std::nullptr_t) const
    {
        return dataPtr == nullptr;
    }

    bool operator!=(std::nullptr_t) const
    {
        return dataPtr != nullptr;
    }

    explicit operator bool() const noexcept
    {
        return dataPtr != nullptr;
    }

    Type* getOwnership() noexcept
    {
        Type* ptr = dataPtr;
        dataPtr = nullptr;
        return ptr;
    }

    void reset(Type* dataPtr_ = nullptr) noexcept
    {
        if (dataPtr != dataPtr_)
        {
            delete dataPtr;
            dataPtr = dataPtr_;
        }
    }

    void ensureNotNull() const
    {
        if (!dataPtr) 
        {
            throw std::runtime_error("A null pointer cannot be dereferenced.");
        }
    }

    Type* operator->()
    {
        ensureNotNull();
        return dataPtr;
    }
    
    Type& operator*()
    {
        ensureNotNull();
        return *dataPtr;
    }

    const Type* operator->() const 
    {
        ensureNotNull();
        return dataPtr;
    }
    
    const Type& operator*() const 
    {
        ensureNotNull();
        return *dataPtr;
    }
};