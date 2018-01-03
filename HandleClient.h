#ifndef HANDLECLIENT_H
#define HANDLECLIENT_H
#include <iostream>
#include <thread_db.h>
#include "CommandsManager.h"


struct clientInfo;
class HandleClient {

private:
    pthread_mutex_t lock;
    pthread_mutex_t killAllLock;
    vector<pthread_t> threads;
    CommandsManager* commandsManager;
    map<string,int> games;

public:
    HandleClient(CommandsManager* commandsManager);
    /**
    * run send message of connection approve. call thread to any coomand.
    * @param clientSocket - number of socket connection of this client
    */
    void run(int clientSocket);
    /**
    * connecting func. connect between this static func of thread to handle func.
    * @param elm - struct of thread func.
    */
    static void* gateToHandle(void* elm);
    /**
    * handle get all commands in diffrent threads
    * @param elm - struct of client info in void cast
    */
    void handle(void* elm);
    void closeAll();
    /**
    * getCommand
    * @param clientSocket - number of socket connection of this client
    * @param command - only the kind of command
    * @return tokens - vector with all the rest of full command.
    */
    vector<string> getCommand(int clientSocket,string &command);
    void eraseThread(pthread_t thread);

};
struct clientInfo {
    int clientSocket;
    HandleClient* handleClient;
    pthread_t thread;
};

#endif //HANDLECLIENT
