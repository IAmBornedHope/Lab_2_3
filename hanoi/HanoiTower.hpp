#pragma once
#include "Ring.hpp"
#include "../stack/Stack.hpp"
#include "../array_sequence/ArraySequence.hpp"

struct HanoiMove {
    size_t start_rod;
    size_t end_rod;
};

template<typename T>
class HanoiTower {
private:
    Stack<T, MutableArraySequence> rods_[3];
    MutableArraySequence<HanoiMove> moves_;
    size_t current_move_;

public:
    HanoiTower();

    void initialize(MutableArraySequence<T>& items, size_t start_rod);
    void generate_moves(size_t count, size_t start_rod, size_t target_rod, size_t helper_rod);
    void do_move();
    const MutableArraySequence<HanoiMove>& get_moves() const;
    size_t get_total_moves() const;

    bool is_finished() const;
    Stack<T, MutableArraySequence>& get_rod(size_t index);

};

#include "HanoiTower.tpp"