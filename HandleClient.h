#ifndef HANDLECLIENT_H
#define HANDLECLIENT_H
#include <iostream>
#include "CommandsManager.h"


struct clientInfo;
class HandleClient {

private:
    pthread_mutex_t lock;
    pthread_mutex_t killAllLock;
    vector<pthread_t> threads;
    CommandsManager commandsManager;
    map<string,int> games;
public:
    HandleClient();
    void run(int clientSocket);
    static void* gate(void* elm);
    void handle(void* elm);
    void closeAll();
    vector<string> getCommand(int clientSocket,string myCommand,string command);
    };
struct clientInfo {
    int clientSocket;
    HandleClient* handleClient;
};

#endif //HANDLECLIENT
