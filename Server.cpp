//Ben Eli 319086435
//Sahar Rofe 209275114
#include "Server.h"
string socketIO::read(){
    //Read char by char until /n
    char c = 0;
    string s = "";
    while(c != '\n'){
        recv(clientID,&c,sizeof(char),0);
        s += c;
    }
    return s;
}
void socketIO::write(string text){
    const char* txt = text.c_str();
    send(clientID ,txt ,strlen(txt) ,0);
}

void socketIO::write(float f){
    ostringstream str;
    str << f;
    string s(str.str());
    write(s);
}
void socketIO::read(float* f){
    recv(clientID,f,sizeof(float),0);
}


Server::Server(int port)throw (const char*) {
    stopped = false;
    // Create a socket (IPv4, TCP)
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        std::cout << "Failed to create socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port); // htons is necessary to convert a number to
    // network byte order
    if (bind(fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cout << "Failed to bind to port. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    // Start listening. Hold at most 5 connections in the queue
    if (listen(fd, 5) < 0) {
        std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Server::start(ClientHandler& ch)throw(const char*){
    t = new thread([&ch,this](){
        while(!stopped){
            socklen_t clientSize = sizeof(client);
            alarm(1);
            int aClient = accept(fd,(struct sockaddr*)&client,&clientSize);
            if(aClient>0){
                //t=new thread([&aClient,this,&ch](){
                ch.handle(aClient);
                close(aClient);
                //});
            }
            alarm(1);

        }
        close(fd);
    });
}
void Server::stop(){
    stopped = true;
    t->join(); // do not delete this!
}

Server::~Server(){
}