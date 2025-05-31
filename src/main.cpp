/* Artem Churilov st130184@student.spbu.ru
    LabWork 3 task "STL-containers" step 2 "Create Template"
*/

#include <iostream>
#include "../include/list.h"

int main()
{
    SkipList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(6);
    std::cout << "List contents: ";
    list.print();
    list.clear();

    list.pop_front();
    std::cout << "List contents: ";
    list.print();
    list.insert(42);
    list.insert(24);
    list.pop_front();
    
    std::cout << "List contents: ";
    list.print();
    return 0;
}