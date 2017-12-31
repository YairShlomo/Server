
#include "HandleClient.h"
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <vector>

using namespace std;
#define MAX 100;
HandleClient::HandleClient(CommandsManager* commandsManager):commandsManager(commandsManager) {
    pthread_mutex_init(&lock,0);
}

void HandleClient::run(int clientSocket) {
    cout << "Client connected" << endl;
    if (clientSocket == -1) {
        throw "Error accepting client";
    }
    cout <<clientSocket << endl;
    pthread_t thread;
    //gameThreads.push_back(thread);
    clientInfo* clientinfo1=new clientInfo;
    clientinfo1->clientSocket=clientSocket;
    clientinfo1->handleClient = this;
    int gT = pthread_create(&thread, NULL,  gate, (void *)clientinfo1);
    //handleClient(clientSocket);
    //close(clientSocket);
}
void* HandleClient::gate(void* elm) {
    clientInfo* info =(clientInfo*)elm;
    info->handleClient->handle(info);
}

void HandleClient::handle(void* elm){
    clientInfo* info =(clientInfo*)elm;
    char buffer[100];

    //string myCommand;
    string command;
    vector<string> tokens = getCommand(info->clientSocket,command,buffer);
    pthread_mutex_lock(&lock);
    commandsManager->executeCommand(command,tokens,info->clientSocket,-1);
    pthread_mutex_unlock(&lock);
}
vector<string> HandleClient::getCommand(int clientSocket,string &command,char* buffer) {
    vector<string> tokens;
    int n;
    n = read(clientSocket, &buffer, sizeof(buffer));
    if (n == -1) {
        throw "Error reading";
    }
    string myCommand(buffer);
    string buf;
    stringstream ss(myCommand);
    ss >> command;
    tokens.push_back(command);
    while (ss >> buf)
        tokens.push_back(buf);
    tokens.erase(tokens.begin());
    return tokens;
}
/*
void HandleClient::closeAll(){
    clientInfo* info;
    string args;
    commandsManager.executeCommand(command,tokens);

}
*/