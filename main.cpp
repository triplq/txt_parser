#include <iostream>
#include <fstream>
#include "Person.h"

using namespace std;

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