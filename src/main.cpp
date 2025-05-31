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

    std::cout << "List contents: ";
    list.print();

    return 0;
}