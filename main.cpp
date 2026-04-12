#include <iostream>
#include "DynamicArray.hpp"

int main() {
    DynamicArray<int> arr(25);
    arr.set(0, 10);
    arr.set(1,1413);

    std::cout << arr.get(0) << std::endl;
    std::cout << arr.get(1) << std::endl;
    std::cout << arr.get_size() << std::endl;
    arr.resize(10);
    std::cout << arr.get_size() << std::endl;
    arr.resize(100);
    std::cout << arr.get_size() << std::endl;
    std::cout << arr.get(50) << std::endl;

}
