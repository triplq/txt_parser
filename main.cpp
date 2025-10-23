#include <iostream>
#include <fstream>
#include "Person.h"
#include <thread>
#include <map>
#include <zmq.hpp>

using namespace std;

void parse_file(string& file_name, vector<Person>& perses){
    ifstream in;
    in.open(file_name);

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
}

vector<Person> only_unique(const vector<Person>& pers1, const vector<Person>& pers2){
    map<Person, size_t> big_pers_file;
    for(size_t i = 0; i  < max(pers1.size(), pers2.size()); i++){
        if(i < pers1.size())
            big_pers_file.insert({pers1[i], 1});
        if(i < pers2.size())
            big_pers_file.insert({pers2[i], 1});
    }
    
    vector<Person> data_to_return;
    for(const auto& elem : big_pers_file){
            data_to_return.push_back(elem.first);
    }

    return data_to_return;

}

void to_file(const vector<Person>& vec){
    ofstream out;
    out.open("send.txt");

    if(out.is_open()){
        for(size_t i = 0; i < vec.size(); i++){
            out << i+1 << ' ' << vec[i] << '\n';
        }
    }
    else
        cout << "Can't open\n";

    out.close();
}

int main(){
    string file_1{"student_file_1.txt"};
    string file_2{"student_file_2.txt"};

    vector<Person> perses_file_1;
    vector<Person> perses_file_2;

    array<thread, 2> th;
    th[0] = thread(parse_file, ref(file_1), ref(perses_file_1));
    th[1] = thread(parse_file, ref(file_2), ref(perses_file_2));

    th[0].join();
    th[1].join();

    vector<Person> vec_to_send = only_unique(perses_file_1, perses_file_2);

    to_file(vec_to_send);

    return 0;
}