#pragma once
#include <iostream>
#include <format>
#include <ctime>

struct PersonID {
    size_t series;
    size_t number;
};

class Person {
private:
    PersonID id_;
    std::string surname_;
    std::string name_;
    std::string patronymic_;
    time_t birth_date_;

public:
    Person() : id_{}, surname_{}, name_{}, patronymic_{}, birth_date_{0} {}

    Person(const PersonID& id, const std::string& surname, const std::string& name,
            const std::string& patronymic, time_t date) : 
            id_{id}, surname_{surname}, name_{name}, patronymic_{patronymic}, birth_date_{date} {}

    PersonID get_id() const { return id_; }
    std::string get_surname() const { return surname_; }
    std::string get_name() const { return name_; }
    std::string get_patronymic() const { return patronymic_; }
    time_t get_birth_date() const { return birth_date_; }

    void set_id(const PersonID& id) { id_ = id; }
    void set_surname(const std::string& surname) { surname_ = surname; }
    void set_name(const std::string& name) { name_ = name; }
    void set_patronymic(const std::string& patronymic) { patronymic_ = patronymic; }
    void set_birth_date(time_t date) { birth_date_ = date; }

    bool operator==(const Person& other) const {
        return id_.series == other.id_.series &&
               id_.number == other.id_.number &&
               surname_ == other.surname_ &&
               name_ == other.name_ &&
               patronymic_ == other.patronymic_ &&
               birth_date_ == other.birth_date_;
    }
    
    bool operator!=(const Person& other) const {
        return !(*this == other);
    }

    std::string get_full_name() const {
        return std::format("{} {} {}", surname_, name_, patronymic_);
    }

    std::string person_to_string() const {
        return std::format("ID: {} {}, ФИО: {}, Дата рождения: {}", id_.series, id_.number, get_full_name(), birth_date_);
    }

};

std::ostream& operator<<(std::ostream& stream, const Person& person) {
    stream << person.person_to_string();
    return stream;
}