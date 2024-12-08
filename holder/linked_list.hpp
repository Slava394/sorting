#pragma once
#include <stdexcept>


template <class Type>
class LinkedList
{
private:
    struct Node
    {
    public:
        Type data;
        Node* next;
        Node* prev;

        Node(const Type& data_) : data(data_), next(nullptr), prev(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t length = 0;

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

    LinkedList(const LinkedList<Type>& otherList)
    {
        Node* current = otherList.head;
        try 
        {
            while (current != nullptr) 
            {
                append(current->data);
                current = current->next;
            }
        }
        catch (...)
        {
            clear();
            throw std::bad_alloc();
        }
    }

    LinkedList(LinkedList&& otherList) noexcept
    {
        head = otherList.head;
        tail = otherList.tail;
        length = otherList.length;
        otherList.head = otherList.tail = nullptr;
        otherList.length = 0;
    }

    ~LinkedList()
    {
        clear();
    }

    LinkedList<Type>& operator=(const LinkedList<Type>& otherList)
    {
        if (this != &otherList)
        {
            Node* backupHead = head;
            Node* backupTail = tail;
            size_t backupLength = length;
            head = nullptr;
            tail = nullptr;
            length = 0;
            Node* current = otherList.head;
            try 
            {
                while (current != nullptr) 
                {
                    append(current->data);
                    current = current->next;
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
        return *this;
    }

    LinkedList<Type>& operator=(LinkedList<Type>&& otherList) noexcept
    {
        if (this != &otherList)
        {
            clear();
            head = otherList.head;
            tail = otherList.tail;
            length = otherList.length;
            otherList.head = otherList.tail = nullptr;
            otherList.length = 0;
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

    Type& getFirst()
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
        return tail->data;
    }

    Type& get(size_t elementIndex) 
    {
        checkIndexRange(elementIndex);
        Node* current = head;
        for (size_t index = 0; index < elementIndex; ++index)
        {
            current = current->next;
        }
        return current->data;
    }

    const Type& getFirst() const
    {
        if (length == 0)
        {
            throw std::invalid_argument("Can`t get first element from an empty list.");
        }
        return head->data;
    }

    const Type& getLast() const
    {
        if (length == 0)
        {
            throw std::invalid_argument("Can`t get last element from an empty list.");
        }
        return tail->data;
    }

    const Type& get(size_t elementIndex) const 
    {
        checkIndexRange(elementIndex);
        Node* current = head;
        for (size_t index = 0; index < elementIndex; ++index)
        {
            current = current->next;
        }
        return current->data;
    }

    size_t getSize() const
    {
        return length;
    }

    void set(const Type& data, size_t elementIndex)
    {
        checkIndexRange(elementIndex);
        Node* current = head;
        for (int index = 0; index < elementIndex; ++index)
        {
            current = current->next;
        }
        current->data = data;
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
        Node* current = head;
        for (int index = 0; index < elementIndex; ++index)
        {
            current = current->next;
        }
        Node* newNode = new Node(data);
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev = newNode;
        newNode->prev->next = newNode;
        length++;
    }

    void prepend(const Type& data)
    {
        Node* newNode = new Node(data);
        if (length == 0)
        {
            tail = head = newNode;
        }
        else
        {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        length++;
    }

    void append(const Type& data)
    {
        Node* newNode = new Node(data);
        if (length == 0)
        {
            tail = head = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
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
        Node* removable = head;
        for (int index = 0; index < elementIndex; ++index)
        {
            removable = removable->next;
        }
        removable->prev->next = removable->next;
        removable->next->prev = removable->prev;
        delete removable;
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
            delete head;
            tail = head = nullptr;
        }
        else
        {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
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
            delete head;
            tail = head = nullptr;
        }
        else
        {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
        length--;
    }

    void clear()
    {
        if (!head)
        {
            return;
        }
        while (head->next != nullptr) 
        {
            removeFirst();
        }
        delete head;
        head = tail = nullptr;
        length = 0;
    }
};