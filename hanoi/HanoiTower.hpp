#pragma once
#include "Ring.hpp"
#include "../stack/Stack.hpp"
#include "../array_sequence/ArraySequence.hpp"

struct Move {
    size_t start_rod;
    size_t end_rod;
};

template<typename T>
class HanoiTower {
private:
    Stack<T, MutableArraySequence> rods_[3];
    MutableArraySequence<Move> moves_;
    size_t current_move_;

public:
    HanoiTower();

    void initialize(MutableArraySequence<T>& items, size_t start_rod);
    void generate_moves(size_t count, size_t start_rod, size_t target_rod, size_t helper_rod);
    void do_move();

    bool is_finished() const;
    Stack<T, MutableArraySequence>& get_rod(size_t index);

};

#include "HanoiTower.tpp"