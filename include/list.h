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
public:
    SkipList() : head(nullptr) {}
    ~SkipList()
    {
        Node* current = head;
        while (current)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    void insert(const T& value)
    {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
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
};

