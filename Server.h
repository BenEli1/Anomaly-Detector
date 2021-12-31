//Ben Eli 319086435
//Sahar Rofe 209275114
#ifndef SERVER_H_
#define SERVER_H_
#include "CLI.h"
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
#include <thread>

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};

class socketIO:public DefaultIO{
    int clientID;
    ifstream in;
    ofstream out;
public:
    socketIO(int clientID):clientID(clientID){}
    virtual string read();
    virtual void write(string text);
    virtual void write(float f);
    virtual void read(float* f);

};
// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int clientID){
        socketIO socketIo(clientID);
        CLI cli(&socketIo);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    sockaddr_in server;
    sockaddr_in client;
    int fd;
    volatile bool stopped;
	thread* t; // the thread to run the start() method in
	// you may add data members

public:
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
