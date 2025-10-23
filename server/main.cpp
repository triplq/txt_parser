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

string only_unique(const vector<Person>& pers1, const vector<Person>& pers2){
    map<Person, size_t> big_pers_file;
    array<thread, 2> th;
    th[0] = thread([&](){
        for(size_t i = 0; i  < pers1.size(); i++)
            big_pers_file.insert({pers1[i], 1});
    });
    th[1] = thread([&](){
        for(size_t i = 0; i < pers2.size(); i++)
            big_pers_file.insert({pers2[i], 1});
    });

    th[0].join();
    th[1].join();

    string data_to_return;
    for(const auto& elem : big_pers_file){
            data_to_return += elem.first.name() + ' ' + elem.first.surname() + ' ' + elem.first.getData() + '\n';
    }

    return data_to_return;

}

string file_to_send(){
    string file_1{"student_file_1.txt"};
    string file_2{"student_file_2.txt"};

    vector<Person> perses_file_1;
    vector<Person> perses_file_2;

    array<thread, 2> th;
    th[0] = thread(parse_file, ref(file_1), ref(perses_file_1));
    th[1] = thread(parse_file, ref(file_2), ref(perses_file_2));

    th[0].join();
    th[1].join();

    return only_unique(perses_file_1, perses_file_2);
}

void server(zmq::context_t& ctx, string& perses){
    thread t([&ctx, &perses](){
        zmq::socket_t socket(ctx, ZMQ_PUB);
        socket.bind("tcp://*:5555");
        while(true)
            socket.send(zmq::buffer(perses));
    });
    t.detach();
}

int main(){
    zmq::context_t context(1);
    string perses = file_to_send();

    cout << perses;

    server(context, perses);
    cout << "Press enter to exit...\n";
    string dummy;
    getline(cin, dummy);

    return 0;
}