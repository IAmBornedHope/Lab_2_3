#include "HanoiTower.hpp"

template<typename T>
HanoiTower<T>::HanoiTower() : current_move_{0} {}


template<typename T>
void HanoiTower<T>::initialize(MutableArraySequence<T>& items, size_t start_rod) {
    for (size_t index = 0; index < items.get_length(); ++index) {
        rods_[start_rod].push(items.get(index));
    }

    size_t target_rod = (start_rod + 1) % 3;
    size_t helper_rod = 3 - start_rod - target_rod;
}