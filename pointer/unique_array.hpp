#pragma once
#include <stdexcept>


template <typename Type>
class UniqueArray
{
private:
    Type* data;

    void release()
    {
        delete[] data;
        data = nullptr;
    }
public:
    explicit UniqueArray(Type* data_ = nullptr)
        : data(data_) {}

    UniqueArray(const UniqueArray<Type>&) = delete;

    UniqueArray(UniqueArray<Type>&& uniqueArray) noexcept
        : data(uniqueArray.data)
    {
        uniqueArray.data = nullptr;
    }

    ~UniqueArray()
    {
        release();
    }

    UniqueArray<Type>& operator=(const UniqueArray<Type>&) = delete;

    UniqueArray<Type>& operator=(UniqueArray<Type>&& uniqueArray) noexcept
    {
        if (data != uniqueArray.data)
        {
            release();
            data = uniqueArray.data;
            uniqueArray.data = nullptr;
        }
        return *this;
    }

    UniqueArray<Type>& operator=(std::nullptr_t) 
    {
        reset();
        return *this;
    }

    bool operator==(const UniqueArray<Type>& uniqueArray) const
    {
        return data == uniqueArray.data;
    }

    bool operator!=(const UniqueArray<Type>& uniqueArray) const
    {
        return data != uniqueArray.data;
    }

    bool operator==(std::nullptr_t) const
    {
        return data == nullptr;
    }

    bool operator!=(std::nullptr_t) const
    {
        return data != nullptr;
    }

    explicit operator bool() const noexcept
    {
        return data != nullptr;
    }

    Type* getOwnership() noexcept
    {
        Type* ptr = data;
        data = nullptr;
        return ptr;
    }

    void reset(Type* data_ = nullptr) noexcept
    {
        if (data != data_)
        {
            delete[] data;
            data = data_;
        }
    }

    void ensureNotNull() const
    {
        if (!data) 
        {
            throw std::runtime_error("A null pointer cannot be dereferenced.");
        }
    }

    Type& operator[](size_t index)
    {
        ensureNotNull();
        return data[index];
    }

    const Type& operator[](size_t index) const
    {
        ensureNotNull();
        return data[index];
    }
};