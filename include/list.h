/* Artem Churilov st130184@student.spbu.ru
    LabWork 3 task "STL-containers" step 2 "Create Template"
*/

#include <iostream>
#include <iterator>
#include <numeric> 
#include <ranges>
template <typename T>
class SkipList
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
        Node(const T& val) : value(val), next(nullptr) {}
    };
    Node* head;
    size_t size_;

    void copyFrom(const SkipList& other)
    {
        if(other.head==nullptr)
        {
            head=nullptr;
            size_=0;
            return;
        }

        head = new Node(other.head->value);
        Node* current = head;
        Node* otherCurrent = other.head-> next;
        
        while(otherCurrent)
        {
            current->next = new Node(otherCurrent->value);
            current = current -> next;
            otherCurrent = otherCurrent -> next;
        }
        size_ = other.size_;
    }
    void clear()
    {
        while (head) 
        {
            pop_front();
        }
    }
public:
    SkipList() : head(nullptr),size_(0) {}
    ~SkipList()
    {
        clear();
    }

    SkipList(const SkipList& other) : head(nullptr), size_(0)
    {
        copyFrom(other);
    }

    SkipList& operator=(const SkipList& other)
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
    public:
        //types
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        //operations
        Iterator(Node* node):current(node){}
        
        Iterator ConstIterator() const
        {
            return ConstIterator(current);
        }

        T& operator*()
        {
            if(!current)
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
            if(!current)
            {
                throw std::runtime_error("Accessing end iterator");
            }
            return &(current->value);
        }
        bool operator==(const Iterator& other) const
        {
            return current==other.current;
        }
        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }
    };
    Iterator begin()
    {
        return Iterator(head);
    };
    Iterator end()
    {
        return Iterator(nullptr);
    };

    class ConstIterator
    {
    private:
        const Node* current;
    public:
        //types
        using iterator_category = std::forward_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;  
        //operations
        ConstIterator(const Node* node) : current(node){};
        ConstIterator(Iterator it) : current(it.operator->()){}

        const T& operator*() const
        {
            if(!current)
            {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return current->value;
        }
        ConstIterator& operator++()
        {
            if(current)
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
            if (!current)
            {
                throw std::runtime_error("Accessing end iterator");
            }
            return &(current->value);
        }
        bool operator==(const ConstIterator& other) const
        {
            return current==other.current;
        }
        bool operator!=(const ConstIterator& other) const
        {
            return !(*this == other);
        }
    };
    ConstIterator begin() const
    {
        return ConstIterator(head);
    };
    ConstIterator end() const
    {
        return ConstIterator(nullptr);
    };
    ConstIterator cbegin() const
    {
        return ConstIterator(head);
    };
    ConstIterator cend() const
    {
        return ConstIterator(nullptr);
    };    

    //info
    bool contains(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->value == value) return true;
            current = current->next;
        }
        return false;
    }

    void print() const
    {
        Node* current = head;
        while (current)
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
    void insert(const T& value)
    {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size_++;
    }
    void pop_front() 
    {
        if (!head) 
        {
            throw std::out_of_range("List is empty");
        }
        
        Node* temp = head;
        head = head->next;
        delete temp;
        size_--;
    }

    bool remove(const T& value)
    {
        if(!head)
        {
            return false;
        }
        if (head->value==value)
        {
            pop_front();
            return true;
        }

        Node* current = head;
        while (current->next)
        {
            if (current->next->value==value)
            {
                Node* temp = current->next;
                current->next=temp->next;
                delete temp;
                size_--;
                return true;
            }
            current=current->next;
        }
        return false;
    }
};

