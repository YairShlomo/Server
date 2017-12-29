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

class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    static void* handleClient(void *clientSocket);
    void handleGame(int clientSocket1, int clientSocket2);
    static void* listening(void *threadId);
    void execute(string myCommand);

};

#endif //SERVER_H
