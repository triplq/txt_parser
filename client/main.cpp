#include <iostream>
#include "Person.h"
#include <zmq.hpp>
#include <thread>

using namespace std;

void client(zmq::context_t& ctx){
    zmq::socket_t socket(ctx, ZMQ_SUB);
    socket.connect("tcp://localhost:5555");
    socket.set(zmq::sockopt::subscribe, "");
    zmq::message_t msg;
    auto res = socket.recv(msg);
    if(!res){
        cout << "Failed to reveive\n";
        return;
    }

    string data(static_cast<char*>(msg.data()), msg.size());
    cout << data;

}

int main(){
    zmq::context_t context(1);
    thread th([&context](){
        client(context);

    });

    th.join();

    cout << "Press Enter to exit...\n";
    string dummy;
    getline(cin, dummy);

    return 0;
}