
#include "HandleClient.h"
#include "Server.h"
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <sys/socket.h>

using namespace std;
#define MAX 100;
HandleClient::HandleClient(CommandsManager* commandsManager):commandsManager(commandsManager)
,threads(){
    pthread_mutex_init(&lock,0);
}

void HandleClient::run(int clientSocket, ThreadPool &pool, vector<Task> &tasks) {
    cout << "Client connected" << endl;
    if (clientSocket == -1) {
        throw "Error accepting client";
    }
    cout <<clientSocket << endl;
    char approval[2] = {'1'};
    int sendApproval = send(clientSocket, &approval[0], 1, 0);
    if (sendApproval < 0) {
        throw "error sending to client";
    }
    //pthread_t thread;
    //gameThreads.push_back(thread);
    clientInfo* clientinfo1=new clientInfo;
    clientinfo1->clientSocket=clientSocket;
    clientinfo1->handleClient = this;
    task= new Task(gateToHandle,(void *)clientinfo1);
    tasks.push_back(*task);
    pool.addTask(task);
   // int gT = pthread_create(&thread, NULL,  gateToHandle, (void *)clientinfo1);
   // clientinfo1->thread=thread;
   // threads.push_back(thread);
}
void* HandleClient::gateToHandle(void* elm) {
    clientInfo* info =(clientInfo*)elm;
    info->handleClient->handle(info);
}
void HandleClient::eraseThread(pthread_t thread ) {
    for (int i=0;i<threads.size(); i++) {
        if (threads[i]==thread) {
            threads.erase(threads.begin() +i);
        }
    }
}

void HandleClient::handle(void* elm){
    clientInfo* info =(clientInfo*)elm;
    //char buffer[100];

    //string myCommand;
    string command;
    vector<string> tokens = getCommand(info->clientSocket,command);
    pthread_mutex_lock(&lock);
    commandsManager->executeCommand(command,tokens,info->clientSocket,-1);
    delete(task);
   // eraseThread(info->thread);
    pthread_mutex_unlock(&lock);
    //threads.erase()
}
vector<string> HandleClient::getCommand(int clientSocket,string &command) {
    vector<string> tokens;
    int n;
    char buffer[100];
    n = recv(clientSocket, &buffer, sizeof(buffer),0);
    //cout<< buffer2  ;
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
void HandleClient::closeAll(){
    for(int i=0; i<threads.size();i++) {
        pthread_cancel(threads[i]);
        cout<<"game"<<i<<"is closed"<<endl;
    }
}
