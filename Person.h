#pragma once

#include <iostream>
#include <chrono>

class Person{
private:
    int day_;
    int month_;
    int year_;
    std::string name_;
    std::string surname_;

    bool isValid(int&, int& , int&);
    
public:
    Person(std::string, std::string, int&, int&, int&);

    int day() const;
    int month() const;
    int year() const;
    std::string name() const;
    std::string surname() const;
    std::string getData() const;

    bool operator == (const Person& other);
    bool operator < (const Person& other);
};

std::ostream& operator<<(std::ostream& stream, const Person& pers);
