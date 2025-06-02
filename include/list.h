/* Artem Churilov st130184@student.spbu.ru
    LabWork 3 task "STL-containers" step 2 "Create Template"
*/

#include <iostream>
#include <iterator>
#include <numeric> 
#include <ranges>
template <typename T>
class CircularList
{
public:
    //types
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
private:
    struct Node
    {
        T value;
        Node* next;
        Node(const T& val=T(),Node* n =nullptr) : value(val), next(n) {}
    };
    Node* dummy;
    size_t size_;

    void copyFrom(const CircularList& other)
    {
        Node* other_current = other.dummy->next;
        Node* last = dummy;
        while (other_current != other.dummy) {
            Node* new_node = new Node(other_current->value, dummy);
            last->next = new_node;
            last = new_node;
            other_current = other_current->next;
        }
        size_ = other.size_;
    }
    void clear()
    {
        while (!empty()) 
        {
            pop_front();
        }
    }
public:
    CircularList() : size_(0) 
    {
        dummy = new Node();
        dummy->next = dummy;
    }
    ~CircularList()
    {
        clear();
        delete dummy;
    }
    CircularList(std::initializer_list<T> init) : CircularList() 
    {
        for (const auto& val : init) 
        {
            push_back(val);
        }
    }
    CircularList(const CircularList& other) : CircularList()
    {
        copyFrom(other);
    }

    CircularList& operator=(const CircularList& other)
    {
        if(this != &other)
        {
            clear();
            copyFrom(other);
        }
        return *this;
    }
        

    //iterators
    class Iterator
    {
    private:
        Node* current;
        Node* dummy;
    public:
        //types
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        //operations
        Iterator(Node* node, Node* dummy_node):current(node),dummy(dummy_node){}
        
        Iterator ConstIterator() const
        {
            return ConstIterator(current);
        }

        T& operator*()
        {
            if(current == dummy || current == nullptr)
            {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return current->value;
        }
        Iterator& operator++()
        {
            if(current)
            {
                current=current->next;
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator temporary = *this;
            ++(*this);
            return temporary;
        }
        T* operator->()
        {
            if(current == dummy || current == nullptr)
            {
                throw std::runtime_error("Accessing end iterator");
            }
            return &(current->value);
        }
        bool operator==(const Iterator& other) const
        {
            return current == other.current && dummy == other.dummy;
        }
        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }
    };
    Iterator begin()
    {
        return Iterator(dummy->next,dummy);
    };
    Iterator end()
    {
        return Iterator(dummy, dummy);
    };

    class ConstIterator
    {
    private:
        const Node* current;
        const Node* dummy;
    public:
        //types
        using iterator_category = std::forward_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;  
        //operations
        ConstIterator(const Node* node, const Node* dummy_node) : current(node), dummy(dummy_node){};
        ConstIterator(Iterator it) : current(it.current),dummy(it.dummy){}

        const T& operator*() const
        {
            if(current == dummy || current == nullptr)
            {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return current->value;
        }
        ConstIterator& operator++()
        {
            if(current != dummy)
            {
                current=current->next;
            }
            return *this;
        }
        ConstIterator operator++(int)
        {
            ConstIterator temporary = *this;
            ++(*this);
            return temporary;
        }
        const T* operator->() const
        {
            if (current == dummy || current == nullptr)
            {
                throw std::runtime_error("Accessing end iterator");
            }
            return &(current->value);
        }
        bool operator==(const ConstIterator& other) const
        {
            return current == other.current && dummy == other.dummy;
        }
        bool operator!=(const ConstIterator& other) const
        {
            return !(*this == other);
        }
    };
    ConstIterator begin() const
    {
        return ConstIterator(dummy->next,dummy);
    };
    ConstIterator end() const
    {
        return ConstIterator(dummy,dummy);
    };
    ConstIterator cbegin() const
    {
        return ConstIterator(dummy->next,dummy);
    };
    ConstIterator cend() const
    {
        return ConstIterator(dummy,dummy);
    };    

    //info
    bool contains(const T& value) const {
        Node* current = dummy->next;
        while (current!=dummy) {
            if (current->value == value) return true;
            current = current->next;
        }
        return false;
    }

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
    
    size_t size() const 
    {
        return size_;
    }
    bool empty() const 
    {
        return size_ == 0;
    }

    //operations
    void push_front(const T& value) {
        Node* newNode = new Node(value, dummy->next);
        dummy->next = newNode;
        size_++;
    }
    void push_back(const T& value)
    {
        Node* last = dummy;
        while (last->next != dummy) 
        {
            last = last->next;
        }
        last->next = new Node(value, dummy);
        size_++;
    }
    void pop_front() 
    {
        if (empty()) 
        {
            throw std::out_of_range("List is empty");
        }
        
        Node* first = dummy->next;
        dummy->next = first->next;
        delete first;
        size_--;
    }

    bool remove(const T& value)
    {
        if(empty())
        {
            return false;
        }
        
        Node* prev = dummy;
        Node* current = dummy->next;
        bool removed = false;

        while (current != dummy) {
            if (current->value == value) {
                prev->next = current->next;
                delete current;
                size_--;
                removed = true;
                current = prev->next;
            } else {
                prev = current;
                current = current->next;
            }
        }
        return removed;
    }
};
