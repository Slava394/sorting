#pragma once
#include <stdexcept>


class Counter 
{
private:
    size_t sharedQuantity;
    size_t weakQuantity;
public:
    Counter(size_t sharedQuantity_, size_t weakQuantity_)
        : sharedQuantity(sharedQuantity_),
          weakQuantity(weakQuantity_) {}

    size_t getSharedCount()
    {
        return sharedQuantity;
    }

    size_t getWeakCount()
    {
        return weakQuantity;
    }

    void increaseSharedCount()
    {
        ++sharedQuantity;
    }

    void increaseWeakCount()
    {
        ++weakQuantity;
    }

    void decreaseSharedCount()
    {
        if (sharedQuantity == 0)
        {
            throw std::logic_error("Shared quantity can`t be less then zero.");
        }
        else
        {
            --sharedQuantity;
        }
    }

    void decreaseWeakCount()
    {
        if (weakQuantity == 0)
        {
            throw std::logic_error("Weak quantity can`t be less then zero.");
        }
        else
        {
            --weakQuantity;
        }
    }
};


template<typename Type>
class WeakPtr;


template<typename Type>
class SharedPtr
{
    friend class WeakPtr<Type>;
private:
    Type* dataPtr;
    Counter* counterPtr;
    
    void release()
    {
        if (counterPtr)
        {
            counterPtr->decreaseSharedCount();
            if (counterPtr->getSharedCount() == 0)
            {
                delete dataPtr;
                dataPtr = nullptr;
            }
            if (counterPtr->getSharedCount() == 0 && counterPtr->getWeakCount() == 0)
            {
                delete counterPtr;
                counterPtr = nullptr;
            }
        }
    }
public:
    explicit SharedPtr(Type* dataPtr_ = nullptr)
        : dataPtr(dataPtr_),
          counterPtr(dataPtr_ ? new Counter(1, 0) : nullptr) {}

    SharedPtr(const SharedPtr<Type>& sharedPtr)
        : dataPtr(sharedPtr.dataPtr),
          counterPtr(sharedPtr.counterPtr)
    {
        if (counterPtr)
        {
            counterPtr->increaseSharedCount();
        }
    }

    explicit SharedPtr(const WeakPtr<Type>& weakPtr);

    SharedPtr(SharedPtr<Type>&&) = delete;

    ~SharedPtr()
    {
        release();
    }

    SharedPtr<Type>& operator=(const SharedPtr<Type>& sharedPtr)
    {
        if (dataPtr != sharedPtr.dataPtr)
        {
            release();
            dataPtr = sharedPtr.dataPtr;
            counterPtr = sharedPtr.counterPtr;
            if (counterPtr)
            {
                counterPtr->increaseSharedCount();
            }
        }
        return *this;
    }

    SharedPtr<Type>& operator=(const WeakPtr<Type>& weakPtr);

    SharedPtr<Type>& operator=(SharedPtr<Type>&&) = delete;

    SharedPtr<Type>& operator=(std::nullptr_t)
    {
        release();
        dataPtr = nullptr;
        counterPtr = nullptr;
        return *this;
    }

    bool operator==(const SharedPtr<Type>& sharedPtr) const
    {
        return dataPtr == sharedPtr.dataPtr;
    }

    bool operator!=(const SharedPtr<Type>& sharedPtr) const
    {
        return dataPtr != sharedPtr.dataPtr;
    }

    bool operator==(const WeakPtr<Type>& weakPtr);

    bool operator!=(const WeakPtr<Type>& weakPtr);

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

    size_t getSharedCount() const
    {
        return counterPtr ? counterPtr->getSharedCount() : 0;
    }

    size_t getWeakCount() const
    {
        return counterPtr ? counterPtr->getWeakCount() : 0;
    }

    Type* operator->()
    {
        return dataPtr;
    }
    
    Type& operator*()
    {
        return *dataPtr;
    }

    const Type* operator->() const
    {
        return dataPtr;
    }
    
    const Type& operator*() const
    {
        return *dataPtr;
    }
};


template<typename Type>
class WeakPtr
{
    friend class SharedPtr<Type>;
private:
    Type* dataPtr;
    Counter* counterPtr;

    void release()
    {
        if (counterPtr)
        {
            counterPtr->decreaseWeakCount();
            if (counterPtr->getSharedCount() == 0 && counterPtr->getWeakCount() == 0)
            {
                delete counterPtr;
                counterPtr = nullptr;
            }
        }
    }
public:
    explicit WeakPtr(std::nullptr_t) 
        : dataPtr(nullptr),
          counterPtr(nullptr) {}

    WeakPtr(const WeakPtr<Type>& weakPtr)
        : dataPtr(weakPtr.dataPtr),
          counterPtr(weakPtr.counterPtr)
    {
        if (counterPtr)
        {
            counterPtr->increaseWeakCount();
        }
    }

    explicit WeakPtr(const SharedPtr<Type>& sharedPtr)
        : dataPtr(sharedPtr.dataPtr),
          counterPtr(sharedPtr.counterPtr)
    {
        if (counterPtr)
        {
            counterPtr->increaseWeakCount();
        }
    }

    WeakPtr(WeakPtr<Type>&&) = delete;

    ~WeakPtr()
    {
        release();
    }

    WeakPtr<Type>& operator=(const WeakPtr<Type>& weakPtr)
    {
        if (dataPtr != weakPtr.dataPtr)
        {
            release();
            dataPtr = weakPtr.dataPtr;
            counterPtr = weakPtr.counterPtr;
            if (counterPtr)
            {
                counterPtr->increaseWeakCount();
            }
        }
        return *this;
    }

    WeakPtr<Type>& operator=(const SharedPtr<Type>& sharedPtr)
    {
        if (dataPtr != sharedPtr.dataPtr)
        {
            release();
            dataPtr = sharedPtr.dataPtr;
            counterPtr = sharedPtr.counterPtr;
            if (counterPtr)
            {
                counterPtr->increaseWeakCount();
            }
        }
        return *this;
    }

    WeakPtr<Type>& operator=(WeakPtr<Type>&&) = delete;

    WeakPtr<Type>& operator=(std::nullptr_t)
    {
        release();
        dataPtr = nullptr;
        counterPtr = nullptr;
        return *this;
    }

    bool operator==(const WeakPtr<Type>& weakPtr) const
    {
        return dataPtr == weakPtr.dataPtr;
    }

    bool operator!=(const WeakPtr<Type>& weakPtr) const
    {
        return dataPtr != weakPtr.dataPtr;
    }

    bool operator==(const SharedPtr<Type>& sharedPtr) const
    {
        return dataPtr == sharedPtr.dataPtr;
    }

    bool operator!=(const SharedPtr<Type>& sharedPtr) const
    {
        return dataPtr != sharedPtr.dataPtr;
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

    size_t getSharedCount() const
    {
        return counterPtr ? counterPtr->getSharedCount() : 0;
    }

    size_t getWeakCount() const
    {
        return counterPtr ? counterPtr->getWeakCount() : 0;
    }

    bool isExpired() const
    {
        return counterPtr ? counterPtr->getSharedCount() == 0 : true;
    }

    SharedPtr<Type> lock()
    {
        if (isExpired())
        {
            return SharedPtr<Type>(); 
        }
        return SharedPtr<Type>(*this);
    }
};


template<typename Type>
SharedPtr<Type>::SharedPtr(const WeakPtr<Type>& weakPtr)
    : dataPtr(nullptr),
      counterPtr(nullptr)
{
    if (!weakPtr.isExpired())
    {
        dataPtr = weakPtr.dataPtr;
        counterPtr = weakPtr.counterPtr;
        counterPtr->increaseSharedCount();
    }
}

template<typename Type>
SharedPtr<Type>& SharedPtr<Type>::operator=(const WeakPtr<Type>& weakPtr)   
{
    if (dataPtr != weakPtr.dataPtr) 
    {
        release();
        if (weakPtr.isExpired())
        {
            dataPtr = nullptr;
            counterPtr = nullptr;
        }
        else 
        {
            dataPtr = weakPtr.dataPtr;
            counterPtr = weakPtr.counterPtr;
            counterPtr->increaseSharedCount();
        }
    }
    return *this;
}

template<typename Type>
bool SharedPtr<Type>::operator==(const WeakPtr<Type>& weakPtr)
{
    return dataPtr == weakPtr.dataPtr;
}

template<typename Type>
bool SharedPtr<Type>::operator!=(const WeakPtr<Type>& weakPtr)
{
    return dataPtr != weakPtr.dataPtr;
}