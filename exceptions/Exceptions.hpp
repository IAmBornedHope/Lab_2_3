#pragma once
#include <exception>

class Exception: public std::exception {
private:
    const char* message_;

public:
    explicit Exception(const char* message) : message_(message) {}
    ~Exception() noexcept override = default;
    const char* what() const noexcept override {
        return message_;
    }
};

class IndexOutOfRangeException: public Exception {
public:
    IndexOutOfRangeException(const char* message) : Exception(message) {}
};

class InvalidArgumentException: public Exception {
public:
    InvalidArgumentException(const char* message) : Exception(message) {}
};

class NullPointerException: public Exception {
public:
    NullPointerException(const char* message) : Exception(message) {}
};

class EmptyListException: public Exception {
public:
    EmptyListException(const char* message) : Exception(message) {}
};

class IteratorPointerException: public Exception {
public:
    IteratorPointerException(const char* message) : Exception(message) {}
};

class BitIndexException: public Exception {
public:
    BitIndexException(const char* message) : Exception(message) {}
};

class SequenceLengthMismatchException: public Exception {
public:
    SequenceLengthMismatchException(const char* message) : Exception(message) {}
};

class DivisionByZeroException: public Exception {
public:
    DivisionByZeroException(const char* message) : Exception(message) {}
};