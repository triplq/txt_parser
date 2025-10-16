#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

class Data{
private:
    // int day;
    // int month;
    // int year;

    bool isValid(int &day, int &month, int &year){
        const chrono::year_month_day ymd((chrono::year(year)), (chrono::month(month)), (chrono::day(day)));
        if(ymd.ok())
            return true;
        else
            return false;
        }
public:
    Data(int d, int m, int y){ 
            if(!isValid(d, m, y))
                throw "Not valid data!";
            else{
                day = d;
                month = m;
                year = y;
            }
    };

    int day;
    int month;
    int year;
};

int main(){
    ifstream in;
    in.open("text.txt");

    vector<Data> dates;

    if(in.is_open()){
        string line;

        while(getline(in, line)){
            try{
                int day, month, year;
                sscanf(line.c_str(), "%*d %*s %*s %d.%d.%d", &day, &month, &year);
                dates.emplace_back(day, month, year);
            }
            catch(const char* msg){
                cout << msg << '\n';
            }
        }
    }
    else
        cout << "Error\n";

    in.close();

    for(auto &dt : dates)
        cout << dt.day << ' ' << dt.month << ' ' << dt.year << '\n';

    return 0;
}