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

    std::string name() const;
    std::string surname() const;
    std::string getData() const;

    bool operator < (const Person& other) const;
};

std::ostream& operator<<(std::ostream& stream, const Person& pers);
