#pragma once
#include <format>
#include "../exceptions/Exceptions.hpp"

template<typename T>
class Complex {
private:
    T re_;
    T im_;

public:
    Complex() : re_{}, im_{} {}

    Complex(T re, T im) : re_{re}, im_{im} {}

    T get_re() const { return re_; }
    T get_im() const { return im_; }

    void set_re(T re) { re_ = re; }
    void set_im(T im) { im_ = im; }

    Complex operator-() const {
        return Complex(-re_, -im_);
    }

    Complex operator+(const Complex& other) const {
        return Complex(re_ + other.re_, im_ + other.im_);
    }

    Complex operator-(const Complex& other) const {
        return Complex(re_ - other.re_, im_ - other.im_);
    }

    Complex operator*(const Complex& other) const {
        T re = (re_ * other.re_) - (im_ * other.im_);
        T im = (re_ * other.im_) + (im_ * other.re_);
        return Complex(re, im);
    }

};
