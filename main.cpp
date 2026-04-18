#include <iostream>
#include <windows.h>
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "ArraySequence.hpp"
#include "Sequence.hpp"

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // DynamicArray<int> arr(25);
    // arr.set(0, 10);
    // arr.set(1,1413);
    // arr.set(2, 22);

    // std::cout << arr.get(0) << std::endl;
    // std::cout << arr.get(1) << std::endl;
    // std::cout << arr.get_size() << std::endl;
    // arr.set(100, 22);
    // LinkedList<int> list;
    // list.append(10);
    // list.append(24);
    // list.append(30);
    // list.append(50);
    // std::cout << list.get_length() << std::endl;
    // list.prepend(17);
    // list.insert_at(1000, 3);
    // std::cout << list.get_node(3)->data << std::endl;

    ArraySequence<int> seq;
    seq.append(4);
    std::cout << seq.get(0) << std::endl;
    

}