#include <iostream>
#include <windows.h>
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "ArraySequence.hpp"
#include "Sequence.hpp"
#include "ListSequence.hpp"

template <typename T>
void PrintSequence(Sequence<T>* seq) {
    std::cout << "[ ";
    for (int i = 0; i < seq->GetLength(); ++i) {
        std::cout << seq->Get(i);
        if (i < seq->GetLength() - 1) std::cout << ", ";
    }
    std::cout << " ]" << std::endl;
}

// Функции-предикаты и преобразователи (можно сделать лямбдами в C++11+, но для наглядности сделаем функциями)

// 1. WHERE: Оставляет только четные числа
bool IsEven(int value) {
    return value % 2 == 0;
}

// 2. MAP: Умножает число на 2
int DoubleValue(int value) {
    return value * 2;
}

// 3. REDUCE: Суммирует элементы
int Sum(int accumulator, int current) {
    return accumulator + current;
}


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

    // ArraySequence<int> seq;
    // seq.append(4);
    // std::cout << seq.get(0) << std::endl;
    
    ListSequence<int> seq;
    seq.append(4);
    std::cout << seq.get(0) << std::endl;

}