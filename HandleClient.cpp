
#include "HandleClient.h"
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <vector>

using namespace std;

HandleClient::HandleClient():commandsManager(games) {
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
    clientInfo* clientInfo=new clientInfo;
    clientInfo->clientSocket=clientSocket;
    clientInfo->handleClient = this;
    int gT = pthread_create(&thread, NULL,  gate, (void *)clientInfo);
    //handleClient(clientSocket);
    //close(clientSocket);
}
void* HandleClient::gate(void* elm) {
    clientInfo* info =(clientInfo*)elm;
    info->handleClient->handle(info);
}

void HandleClient::handle(void* elm){
    clientInfo* info =(clientInfo*)elm;
    string myCommand;
    string command;
    vector<string> tokens = getCommand(info->clientSocket,myCommand,command);
    pthread_mutex_lock(&lock);
    commandsManager.executeCommand(command,tokens,info);
    pthread_mutex_unlock(&lock);

}
vector<string> getCommand(int clientSocket,string myCommand,string command) {
    vector<string> tokens;
    int n;
    n = read(clientSocket, &myCommand, sizeof(myCommand));
    if (n == -1) {
        cout << "Error reading" << endl;
        return NULL;
    }
    string buf;
    stringstream ss(myCommand);
    ss >> command;
    tokens.push_back(command);
    while (ss >> buf)
        tokens.push_back(buf);
    tokens.erase(tokens.begin());
    return tokens;
}
void HandleClient::closeAll(){
    ClientInfo* info;
    string args;
    commandsManager.executeCommand(command,tokens);

}
