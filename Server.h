#ifndef SERVER_H_
#define SERVER_H_
#include "CLI.h"
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <unistd.h> // For read
#include <stdio.h>
#include <pthread.h>
#include <thread>
#include<signal.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};

class socketIO:public DefaultIO{
    int clientID;
public:
    socketIO(int clientID):clientID(clientID){
    }
    virtual string read();
    virtual void write(string text);
    virtual void write(float f);
    virtual void read(float* f);
};
// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
    CLI* cli = nullptr;
	public:
    virtual void handle(int clientID){
        socketIO socketIo(clientID);
        cli = new CLI(&socketIo);
        //CLI cli(&socketIo);
        cli->start();
        delete cli;
    }
};


// implement on Server.cpp
class Server {
    int fileDescriptor;
    volatile bool stopped;//volatile because of multi-threading
    sockaddr_in server;//server address
    sockaddr_in client;//client address
	thread* t; // the thread to run the start() method in
	// you may add data members

public:
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
