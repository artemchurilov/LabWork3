/* Artem Churilov st130184@student.spbu.ru
    LabWork 3 task "STL-containers" step 3 "Documentary"
*/
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>

/*!
@class CircularList
@brief A circular doubly-linked list container template.

@tparam T Type of elements stored in the list.
*/

template <typename T>
class CircularList
{
public:
    // Type definitions for STL compatibility
    using value_type = T;             ///< Type of stored elements
    using reference = T&;              ///< Reference to element
    using const_reference = const T&;  ///< Const reference to element
    using size_type = std::size_t;     ///< Size type
    using difference_type = std::ptrdiff_t; ///< Iterator difference type

private:
    // Internal node structure
    struct Node
    {
        T value;        ///< Stored value
        Node* next;     ///< Pointer to next node
        Node* prev;     ///< Pointer to previous node
        /*! Node constructor. */
        Node(const T& val=T(),Node* n =nullptr,Node* p = nullptr) : value(val), next(n),prev(p) {}
    };
    Node* dummy;    ///< Dummy node marking list boundaries
    size_t size_;   ///< Current number of elements

    /*! @brief Copies elements from another list. */
    void copyFrom(const CircularList& other)
    {
        Node* other_current = other.dummy->next;
        Node* last = dummy;
        while (other_current != other.dummy)
        {
            Node* new_node = new Node(other_current->value, dummy, last);
            last->next = new_node;
            last = new_node;
            other_current = other_current->next;
        }
        dummy->prev = last;
        size_ = other.size_;
    }

public:
     // Construction/destruction
    /*! @brief Default constructor. Creates empty list. */
    CircularList() : size_(0)
    {
        dummy = new Node();
        dummy->next = dummy;
        dummy->prev = dummy;
    }

    /*! @brief Destructor. Clears all elements. */
    ~CircularList()
    {
        clear();
        delete dummy;
    }
        /*! 
    @brief Initializer list constructor.
    @param init List of elements to initialize with.
    */
    CircularList(std::initializer_list<T> init) : CircularList()
    {
        for (const auto& val : init)
        {
            push_back(val);
        }
    }
    /*! @brief Copy constructor. */
    CircularList(const CircularList& other) : CircularList()
    {
        copyFrom(other);
    }
    /*! @brief Copy assignment operator. */
    CircularList& operator=(const CircularList& other)
    {
        if(this != &other)
        {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    /*!
    @class CircularList::Iterator
    @brief Bidirectional iterator for CircularList.
    */
    class Iterator
    {
    private:
        Node* current;
        Node* dummy;
    public:
        /*! @brief Default constructor. */
        Iterator() : current(nullptr), dummy(nullptr) {}
        // Iterator traits for STL compatibility
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /*! 
        @brief Parameterized constructor.
        @param node Starting node
        @param dummy_node Sentinel node for boundary checks
        */
        Iterator(Node* node, Node* dummy_node):current(node),dummy(dummy_node) {}
        /*! @brief Conversion from const iterator. */
        Iterator ConstIterator() const
        {
            return ConstIterator(current);
        }

        /*! @brief Dereference operator. */
        T& operator*() const
        {
            if(current == dummy || current == nullptr)
            {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return current->value;
        }

        /*! @brief Prefix increment. */
        Iterator& operator++()
        {
            if(current)
            {
                current=current->next;
            }
            return *this;
        }
        /*! @brief Postfix increment. */
        Iterator operator++(int)
        {
            Iterator temporary = *this;
            ++(*this);
            return temporary;
        }
        /*! @brief Prefix decrement. */
        Iterator& operator--()
        {
            if (current)
            {
                current = current->prev;
            }
            return *this;
        }
        /*! @brief Postfix decrement. */
        Iterator operator--(int)
        {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }
        /*! @brief Member access operator. */
        T* operator->() const
        {
            if(current == dummy || current == nullptr)
            {
                throw std::runtime_error("Accessing end iterator");
            }
            return &(current->value);
        }
        /*! @brief Equality comparison. */
        bool operator==(const Iterator& other) const
        {
            return current == other.current && dummy == other.dummy;
        }

        /*! @brief Inequality comparison. */
        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }
    };
    // Iterators
    /*! @brief Returns iterator to first element. */
    Iterator begin()
    {
        return Iterator(dummy->next,dummy);
    };
    /*! @brief Returns iterator to end. */
    Iterator end()
    {
        return Iterator(dummy, dummy);
    };
    /*!
    @class CircularList::ConstIterator
    @brief Constant bidirectional iterator for CircularList.
    */
    class ConstIterator
    {
    private:
        const Node* current;
        const Node* dummy;
    public:
        /*! @brief Default constructor. */
        ConstIterator() : current(nullptr), dummy(nullptr) {}
        // Iterator traits for STL compatibility
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        /*! 
        @brief Parameterized constructor.
        @param node Starting node
        @param dummy_node Sentinel node for boundary checks
        */
        ConstIterator(const Node* node, const Node* dummy_node) : current(node), dummy(dummy_node) {};

        /*! @brief Conversion from mutable iterator. */
        ConstIterator(Iterator it) : current(it.current),dummy(it.dummy) {}
        /*! @brief Dereference operator. */
        const T& operator*() const
        {
            if(current == dummy || current == nullptr)
            {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return current->value;
        }
        /*! @brief Prefix increment. */
        ConstIterator& operator++()
        {
            if(current != dummy)
            {
                current=current->next;
            }
            return *this;
        }
        /*! @brief Postfix increment. */
        ConstIterator operator++(int)
        {
            ConstIterator temporary = *this;
            ++(*this);
            return temporary;
        }
        /*! @brief Prefix decrement. */
        ConstIterator& operator--()
        {
            if (current)
            {
                current = current->prev;
            }
            return *this;
        }

        /*! @brief Postfix decrement. */
        ConstIterator operator--(int)
        {
            ConstIterator tmp = *this;
            --(*this);
            return tmp;
        }

        /*! @brief Member access operator. */
        const T* operator->() const
        {
            if (current == dummy || current == nullptr)
            {
                throw std::runtime_error("Accessing end iterator");
            }
            return &(current->value);
        }
        /*! @brief Equality comparison. */
        bool operator==(const ConstIterator& other) const
        {
            return current == other.current && dummy == other.dummy;
        }

        /*! @brief Inequality comparison. */
        bool operator!=(const ConstIterator& other) const
        {
            return !(*this == other);
        }
    };
    /*! @brief Returns const iterator to first element. */
    ConstIterator begin() const
    {
        return ConstIterator(dummy->next,dummy);
    };
    /*! @brief Returns const iterator to end (sentinel). */
    ConstIterator end() const
    {
        return ConstIterator(dummy,dummy);
    };
    /*! @brief Returns const iterator to first element. */
    ConstIterator cbegin() const
    {
        return ConstIterator(dummy->next,dummy);
    };
    /*! @brief Returns const iterator to end (sentinel). */
    ConstIterator cend() const
    {
        return ConstIterator(dummy,dummy);
    };

    // Operations
    /*! 
    @brief Checks if value exists in list.
    @param value Value to search for
    @return true if value found
    */
    bool contains(const T& value) const
    {
        Node* current = dummy->next;
        while (current!=dummy)
        {
            if (current->value == value) return true;
            current = current->next;
        }
        return false;
    }
    /*! @brief Prints elements to std::cout. */
    void print() const
    {
        Node* current = dummy->next;
        while (current!=dummy)
        {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
    // Capacity
    /*! @brief Checks if list is empty. */
    bool empty() const
    {
        return size_ == 0;
    }
    /*! @brief Returns number of elements. */
    size_t size() const
    {
        return size_;
    }
    // Modifiers
    /*! 
    @brief Clears all elements.
    @post size() == 0
    */
    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }
    /*! 
    @brief Adds element to front.
    @param value Element to add
    */
    void push_front(const T& value)
    {
        Node* newNode = new Node(value, dummy->next, dummy);
        dummy->next->prev = newNode;
        dummy->next = newNode;
        size_++;
    }
    /*! 
    @brief Adds element to back.
    @param value Element to add
    */
    void push_back(const T& value)
    {
        Node* last = dummy->prev;
        Node* newNode = new Node(value, dummy, last);
        last->next = newNode;
        dummy->prev = newNode;
        size_++;
    }
    /*! 
    @brief Removes first element.
    @throws std::out_of_range if empty
    */
    void pop_front()
    {
        if (empty()) throw std::out_of_range("List is empty");

        Node* first = dummy->next;
        dummy->next = first->next;
        first->next->prev = dummy;
        delete first;
        size_--;
    }
    /*! 
    @brief Removes first occurrence of value.
    @param value Element value to remove
    @return true if element was removed
    */
    bool remove(const T& value)
    {
        if(empty())
        {
            return false;
        }

        Node* prev = dummy;
        Node* current = dummy->next;
        bool removed = false;

        while (current != dummy)
        {
            if (current->value == value)
            {
                prev->next = current->next;
                current->next->prev = prev;
                delete current;
                size_--;
                removed = true;
                current = prev->next;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
        return removed;
    }
};
// Static assertions for iterator concepts
static_assert(std::bidirectional_iterator<CircularList<int>::Iterator>);
static_assert(std::bidirectional_iterator<CircularList<int>::ConstIterator>);
static_assert(std::ranges::bidirectional_range<CircularList<int>>);

static_assert(std::is_default_constructible_v<CircularList<int>::Iterator>);
static_assert(std::is_copy_constructible_v<CircularList<int>::Iterator>);
static_assert(std::is_destructible_v<CircularList<int>::Iterator>);

#endif