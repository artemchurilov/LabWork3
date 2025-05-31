/* Artem Churilov st130184@student.spbu.ru
    LabWork 3 task "STL-containers" step 2 "Create Template"
*/

#include <iostream>

template <typename T>
class SkipList
{
private:
    struct Node
    {
        T value;
        Node* next;
        Node(const T& val) : value(val), next(nullptr) {}
    };
    Node* head;
    size_t size;
public:
    SkipList() : head(nullptr),size(0) {}
    ~SkipList()
    {
        clear();
    }

    //iterators
    class Iterator
    {
    private:
        Node* current;
    public:
        Iterator(Node* node):current(node){}
        T& operator*()
        {
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
    
    size_t get_size() const {
        return size;
    }
    bool is_empty() const {
        return size == 0;
    }

    //operations
    void insert(const T& value)
    {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
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
        size--;
    }
    void clear()
    {
        while (head) 
        {
            pop_front();
        }
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
                size--;
                return true;
            }
            current=current->next;
        }
        return false;
    }
};

