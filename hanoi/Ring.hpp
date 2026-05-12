#pragma once
#include <cstddef>

enum class Color {
    Red,
    Green,
    Blue,
    Yellow,
    Pink,
    Orange
};

enum class Shape {
    Circle,
    Square,
    Triangle
};

class Ring {
private:
    size_t size_;
    Shape shape_;
    Color color_;
public:
    Ring(size_t size = 0, Color color = Color::Red, Shape shape = Shape::Circle) : size_{size}, color_{color}, shape_{shape} {}

    size_t get_size() const { return size_; }
    Shape get_shape() const { return shape_; }
    Color get_color() const { return color_; }

    bool operator>(const Ring& ring) const {
        return size_ > ring.size_;
    }

    bool operator<(const Ring& ring) const {
        return size_ < ring.size_;
    }

    bool operator==(const Ring& ring) const {
        return size_ == ring.size_;
    }

};