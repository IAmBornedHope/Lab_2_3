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

    size_t count = items.get_length();

    generate_moves(count, start_rod, target_rod, helper_rod);
}

template<typename T>
void HanoiTower<T>::generate_moves(size_t count, size_t start_rod, size_t target_rod, size_t helper_rod) {
    if (count == 0) {
        return;
    }

    generate_moves(count - 1, start_rod, helper_rod, target_rod);
    moves_.append(Move(start_rod, target_rod));
    generate_moves(count - 1, helper_rod, target_rod, start_rod);
}

template<typename T>
void HanoiTower<T>::do_move() {
    Move current = moves_.get(current_move_);
    size_t start_index = current.start_rod;
    size_t target_index = current.end_rod;

    T item = rods_[start_index].top();
    rods_[start_index].pop();
    rods_[target_index].push(item);

    current_move_++;
}

template<typename T>
bool HanoiTower<T>::is_finished() const {
    return current_move_ >= moves_.get_length();
}

template<typename T>
Stack<T, MutableArraySequence>& HanoiTower<T>::get_rod(size_t index) {
    return rods_[index];
}