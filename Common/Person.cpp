#include "Person.h"

Person::Person(std::string n, std::string sn, int& d, int& m, int& y) : name_(n), surname_(sn){ 
    if(!isValid(d, m, y))
        throw "Not valid data!";

    day_ = d;
    month_ = m;
    year_ = y;
};

bool Person::isValid(int &day, int &month, int &year){
    const std::chrono::year_month_day ymd((std::chrono::year(year)), (std::chrono::month(month)), (std::chrono::day(day)));
    if(ymd.ok())
        return true;
    else
        return false;
}

std::string Person::name() const{ return name_; };
std::string Person::surname() const{ return surname_; };
std::string Person::getData() const{ return std::to_string(day_) + '.' + std::to_string(month_) + '.' + std::to_string(year_); };

bool Person::operator<(const Person& other) const{
    if((name_ + surname_ < other.name_ + other.surname_) || (name_ + surname_ == other.name_ + other.surname_ && this->getData() < other.getData()))
        return true;
    else
        return false;
};

std::ostream& operator<<(std::ostream& stream, const Person& pers){
    stream << pers.name() << ' ' << pers.surname() << ' ' << pers.getData();
    return stream;
}