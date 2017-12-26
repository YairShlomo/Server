/*
Name:Yair Shlomo
ID: 308536150
Name:Gal Eini
ID: 305216962
*/
#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H
#include<vector>
#include <pthread.h>
#include <cstdlib>
#include<sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
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
};

#endif //UNTITLED_SERVER_H
