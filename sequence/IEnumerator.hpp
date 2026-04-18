#pragma once

template<class T, template<typename> class Derived>
class IEnumerator {
public:
    using ptr = T*;
    using rfr = T&;

    rfr operator*() {
        return derived().operator*();
    }
    
    Derived<T>& operator++() {
        derived().operator++();
        return *this;
    }

private:
    Derived<T>& derived() {
        return static_cast<Derived<T>&>(*this);
    }
    
    const Derived<T>& derived() const {
        return static_cast<const Derived<T>&>(*this);
    }
};