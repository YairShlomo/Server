/*
Name:Yair Shlomo
ID: 308536150
Name:Gal Eini
ID: 305216962
*/

#include <sstream>
#include <thread_db.h>
#include "Server.h"
#include "HandleClient.h"
#include "ThreadPool.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

#define TASKS_NUM 5
map <string,int> Game;
Server::Server(int port,HandleClient handleClient): port(port), serverSocket(0),handleClient(handleClient),clients(),pool(THREADS_NUM) {
    serverIsRunning=false;
    cout << "Server" << endl;
}

void Server::start() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        throw "Error opening socket";
    }
    struct sockaddr_in serverAddress;
    // Assign a local address to the socket
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    if (listen(serverSocket, MAX_CONNECTED_CLIENTS) < 0) {
        throw "Error listening to socket";
    }

    pthread_t thread;
    int rc = pthread_create(&thread, NULL, gate, this);
    if (rc) {
        cout << "Error ,unable to create thread" << rc << endl;
        exit(-1);
    }
    while (true) {
    string name;
    cin >> name;
    //char buffer[5] = {"END"};
        if (name=="exit") {
            pool.terminate();

            for (int i = 0; i < tasks.size(); i++) {
               // delete tasks[i];
                tasks.erase(tasks.begin()+i);
                cout << "client" << i+1 << "is closed";
            }
            serverIsRunning=true;
            cout << "Server is closed" << endl;
            close(serverSocket);
            exit(0);
        }
    }
}
void* Server::gate(void* elm) {
                Server *server = (Server *) elm;
                try {
                    server->listening();
                } catch (const char *message) {
                    cout << "can't start server:" << message << endl;
                    exit(-1);
                }
            }
void Server::listening() {
    struct sockaddr_in clientAddress;
    //long serversocket = (long)sSocket;
    socklen_t clientAddressLen = sizeof(clientAddress);
    //ThreadPool pool(THREADS_NUM);
    while (!serverIsRunning) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct
                sockaddr *) &clientAddress, &clientAddressLen);

        clients.push_back(clientSocket);
        handleClient.run(clientSocket, pool, tasks);
    }
}



