#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

class Person{
private:
    int day_;
    int month_;
    int year_;
    string name_;
    string surname_;

    bool isValid(int &day, int &month, int &year){
        const chrono::year_month_day ymd((chrono::year(year)), (chrono::month(month)), (chrono::day(day)));
        if(ymd.ok())
            return true;
        else
            return false;
    }
    
public:
    Person(string n, string sn, int d, int m, int y) : name_(n), surname_(sn){ 
            if(!isValid(d, m, y))
                throw "Not valid data!";

            day_ = d;
            month_ = m;
            year_ = y;
    };

    int day() const{ return day_; };
    int month() const{ return month_; };
    int year() const{ return year_; };
    string name() const{ return name_; };
    string surname() const{ return surname_; };
    string getData() const{ return to_string(day_) + '.' + to_string(month_) + '.' + to_string(year_); };
};

ostream& operator<<(ostream& stream, const Person& pers){
    stream << pers.name() << ' ' << pers.surname() << ' ' << pers.getData();
    return stream;
}

int main(){
    ifstream in;
    in.open("text.txt");

    vector<Person> perses;

    if(in.is_open()){
        string line;

        while(getline(in, line)){
            try{
                int day, month, year;
                char buffer_name[50], buffer_surname[50];
                sscanf(line.c_str(), "%*d %s %s %d.%d.%d", &buffer_name, &buffer_surname, &day, &month, &year);
                perses.emplace_back(buffer_name, buffer_surname, day, month, year);
            }
            catch(const char* msg){
                cout << msg << '\n';
            }
        }
    }
    else
        cout << "Not open\n";

    in.close();

    for(const auto& ps: perses)
        cout << ps << '\n';

    return 0;
}