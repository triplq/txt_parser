#include <iostream>
#include <fstream>
#include "Person.h"
#include <thread>
#include <algorithm>

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

template<typename T>
void BubbleSort(vector<T>& vec){
    bool swapped;
    for(size_t i = 0; i < vec.size(); i++){
        swapped = false;
        for(size_t j = 0; j < vec.size()-i-1; i++){
            if(vec[j+1] < vec[j]){
                swapped = true;
                swap(vec[j], vec[j+1]);
            }
        }
        if(!swapped)
            break;
    }
}

vector<Person> deleting_same(vector<Person>& pers1, vector<Person>& pers2){
    BubbleSort(pers1);
    BubbleSort(pers2);

    return pers1;
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

    vector<Person> file_to_send = deleting_same(perses_file_1, perses_file_2);

    return 0;
}