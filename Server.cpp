//Ben Eli 319086435
//Sahar Rofe 209275114
#include "Server.h"
#include <thread>

string socketIO::read(){

}
void socketIO::write(string text){

}

void socketIO::write(float f){

}

void socketIO::read(float* f){
}

Server::Server(int port)throw (const char*) {
    // Create a socket (IPv4, TCP)
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cout << "Failed to create socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }
    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(port); // htons is necessary to convert a number to
    // network byte order
    if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        std::cout << "Failed to bind to port. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    // Start listening. Hold at most 10 connections in the queue
    if (listen(sockfd, 10) < 0) {
        std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }


}


void Server::start(ClientHandler& ch)throw(const char*){
    t=new thread([&ch,this](){signal(SIGALRM,sigHandler);

    }


    }


void Server::stop(){
    t->join(); // do not delete this!
}

Server::~Server() {
}