/*
Name:Yair Shlomo
ID: 308536150
Name:Gal Eini
ID: 305216962
*/
#ifndef SERVER_H
#define SERVER_H
#include<vector>
#include <pthread.h>
#include <cstdlib>
#include<sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "CommandsManager.h"
#include "HandleClient.h"
#include <thread_db.h>

/**
 * Server is managing any client want to connecet.
*/
class Server {
public:
    Server(int port,HandleClient handleClient);
    /**
    * start intiailizing server and start listen to clients.call threads for clients to connect
    */
    void start();
    map<string,int> games;
    void listening();


private:
    int port;
    int serverSocket; // the socket's server
    HandleClient handleClient;
    bool stopServer;
    static void* gate(void* elm);
    vector<int> clients;



    };

#endif //SERVER_H
