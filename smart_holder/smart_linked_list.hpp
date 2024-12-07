#pragma once
#include <stdexcept>
#include "pointer/shared_weak_ptr.hpp"
#include "pointer/unique_ptr.hpp"


template <class Type>
class LinkedList
{
private:
    struct Node
    {
    public:
        Type data;
        SharedPtr<Node> next;

        Node() : data(Type()), next(nullptr) {}
        Node(const Type& data_) : data(data_), next(nullptr) {}
    };

    SharedPtr<Node> head;
    WeakPtr<Node> tail;
    size_t length;

    void copyFrom(const LinkedList<Type>& otherList)
    {
        SharedPtr<Node> backupHead = head;
        WeakPtr<Node> backupTail = tail;
        size_t backupLength = length;
        head = nullptr;
        tail = nullptr;
        length = 0;
        SharedPtr<Node> currentNode = otherList.head;
        try
        {
            while (currentNode != nullptr) 
            {
                append(currentNode->data);
                currentNode = currentNode->next;
            }
        }
        catch (...)
        {
            clear();
            head = backupHead;
            tail = backupTail;
            length = backupLength;
            throw std::bad_alloc();
        }
    }

    void moveFrom(LinkedList<Type>& otherList)
    {
        head = otherList.head;
        tail = otherList.tail;
        length = otherList.length;
        otherList.head = nullptr;
        otherList.length = 0;
    }

    void checkIndexRange(size_t index) const
    {
        if (index >= length)
        {
            throw std::out_of_range("Index out of range.");
        }
    }
public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    
    LinkedList(const Type* items, size_t count) : head(nullptr), tail(nullptr), length(0)
    {
        if (count < 0)
        {
            throw std::invalid_argument("Can`t create list with negative length.");
        }
        try
        {
            for (size_t index = 0; index < count; ++index)
            {
                append(items[index]);
            }
        }
        catch (...)
        {
            clear();
            throw std::bad_alloc();
        }
    }

    LinkedList(const LinkedList<Type>& otherList) : head(nullptr), tail(nullptr), length(0)
    {
        copyFrom(otherList);
    }

    LinkedList(LinkedList&& otherList) noexcept : head(nullptr), tail(nullptr), length(0)
    {
        moveFrom(otherList);
    }

    LinkedList<Type>& operator=(const LinkedList<Type>& otherList)
    {
        if (this != &otherList)
        {
            copyFrom(otherList);
        }
        return *this;
    }

    LinkedList<Type>& operator=(LinkedList<Type>&& otherList) noexcept
    {
        if (this != &otherList)
        {
            clear();
            moveFrom(otherList);
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

    // LinkedList<Type>& operator+=(LinkedList<Type>& otherList)
    // {
    //     concat(otherList);
    //     return *this;
    // }

    Type& getFirst()
    {
        if (length == 0)
        {
            throw std::invalid_argument("Can`t get first element from an empty list.");
        }
        return head->data;
    }

    const Type& getFirst() const
    {
        if (length == 0)
        {
            throw std::invalid_argument("Can`t get first element from an empty list.");
        }
        return head->data;
    }

    Type& getLast()
    {
        if (length == 0)
        {
            throw std::invalid_argument("Can`t get last element from an empty list.");
        }
        return tail.lock()->data;
    }

    const Type& getLast() const
    {
        if (length == 0)
        {
            throw std::invalid_argument("Can`t get last element from an empty list.");
        }
        return tail.lock()->data;
    }

    Type& get(size_t elementIndex) 
    {
        checkIndexRange(elementIndex);
        SharedPtr<Node> currentNode = head;
        for (size_t index = 0; index < elementIndex; ++index)
        {
            currentNode = currentNode->next;
        }
        return currentNode->data;
    }

    const Type& get(size_t elementIndex) const 
    {
        checkIndexRange(elementIndex);
        SharedPtr<Node> currentNode = head;
        for (size_t index = 0; index < elementIndex; ++index)
        {
            currentNode = currentNode->next;
        }
        return currentNode->data;
    }

    size_t getSize() const
    {
        return length;
    }

    void set(const Type& data, size_t elementIndex)
    {
        checkIndexRange(elementIndex);
        SharedPtr<Node> currentNode = head;
        for (int index = 0; index < elementIndex; ++index)
        {
            currentNode = currentNode->next;
        }
        currentNode->data = data;
    }

    void insertAt(const Type& data, size_t elementIndex)
    {
        if (elementIndex > length)
        {
            throw std::out_of_range("Index out of range.");
        }
        if (elementIndex == 0)
        {
            prepend(data);
            return;
        }
        if (elementIndex == length)
        {
            append(data);
            return;
        }
        SharedPtr<Node> prev = head, next;
        for (int index = 0; index + 1 < elementIndex; ++index)
        {
            prev = prev->next;
        }
        next = prev->next;
        SharedPtr<Node> newNode(new Node(data));
        prev->next = newNode;
        newNode->next = next;
        length++;
    }

    void prepend(const Type& data)
    {
        SharedPtr<Node> newNode(new Node(data));
        if (length == 0)
        {
            tail = head = newNode;
        }
        else
        {
            SharedPtr<Node> prevHead = head;
            head = newNode;
            head->next = prevHead;
        }
        length++;
    }

    void append(const Type& data)
    {
        SharedPtr<Node> newNode(new Node(data));
        if (length == 0)
        {
            tail = head = newNode;
        }
        else
        {
            tail.lock()->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void erase(size_t elementIndex)
    {
        checkIndexRange(elementIndex);
        if (elementIndex == 0)
        {
            removeFirst();
            return;
        }
        if (elementIndex + 1 == length)
        {
            removeLast();
            return;
        }
        SharedPtr<Node> prev = head, next, removable;
        for (int index = 0; index + 1 < elementIndex; ++index)
        {
            prev = prev->next;
        }
        removable = prev->next;
        next = removable->next;
        prev->next = next;
        length--;
    }

    void removeFirst()
    {
        if (length == 0)
        {
            throw std::out_of_range("Can`t remove first element from an empty list.");
        }
        else if (length == 1)
        {
            tail = head = nullptr;
        }
        else
        {
            SharedPtr<Node> newHead = head->next;
            head = newHead;
        }
        length--;
    }

    void removeLast()
    {
        if (length == 0)
        {
            throw std::out_of_range("Can`t remove last element from an empty list.");
        }
        else if (length == 1)
        {
            tail = head = nullptr;
        }
        else
        {
            SharedPtr<Node> currentNode = head;
            while (currentNode->next->next != nullptr)
            {
                currentNode = currentNode->next;
            }
            currentNode->next = nullptr;
            tail = currentNode;
        }
        length--;
    }

    // UniquePtr<LinkedList<Type>> getSubList(int startIndex, int endIndex)
    // {
    //     checkIndexRange(startIndex);
    //     if (endIndex > length)
    //     {
    //         throw std::out_of_range("Index out of range.");
    //     }
    //     if (startIndex >= endIndex)
    //     {
    //         throw std::logic_error("End index can`t be less then start index.");
    //     }
    //     auto subsequence = UniquePtr<LinkedList<Type>>(new LinkedList<Type>());
    //     for (int index = startIndex; index < endIndex; ++index) 
    //     {
    //         subsequence->append(get(index));
    //     }
    //     return subsequence;
    // }

    // void concat(const LinkedList<Type>& otherList)
    // {
    //     if (otherList.length == 0)
    //     {
    //         return;
    //     }
    //     else
    //     {
    //         SharedPtr<Node> tail = head;
    //         while (tail->next != nullptr)
    //         {
    //             tail = tail->next;
    //         }
    //         SharedPtr<Node> currentNode = otherList.head;
    //         SharedPtr<Node> newNode(new Node(currentNode->data));
    //         tail->next = newNode;
    //         while (currentNode->next != nullptr)
    //         {
    //             tail = tail->next;
    //             currentNode = currentNode->next;
    //             SharedPtr<Node> newNode(new Node(currentNode->data));
    //             tail->next = newNode;
    //         }
    //         length += otherList.length;
    //     }
    // }

    void clear()
    {
        head = nullptr;
        length = 0;
    }
};