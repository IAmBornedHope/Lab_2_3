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

class TryToChangeImmutableException: public Exception {
public:
    TryToChangeImmutableException(const char* message) : Exception(message) {}
};

class NullPointerException: public Exception {
public:
    NullPointerException(const char* message) : Exception(message) {}
};

class EmptyListException: public Exception {
public:
    EmptyListException(const char* message) : Exception(message) {}
};