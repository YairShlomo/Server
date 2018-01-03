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

using namespace std;
#define MAX_CONNECTED_CLIENTS 10
map <string,int> Game;
Server::Server(int port,HandleClient handleClient): port(port), serverSocket(0),handleClient(handleClient),clients() {
    stopServer=false;
    cout << "Server" << endl;
}

void Server::start() {
    char *name;
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
    cin >> name;
    char buffer[5] = {"END"};
    while (true) {
        if (strcmp(name, "exit") == 0) {
            handleClient.closeAll();
            for (vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
                close(*it);
                cout << "client" << *it << "is closed";
            }
            stopServer=true;
            cout << "Server is closed" << endl;
            close(serverSocket);
        }
    }
}
            /*
            for (vector<thread_t>::iterator it = threadArgs->threads.begin(); it != threadArgs->threads.end(); ++it) {
                pthread_cancel(*it);
            }
            for (vector<int>::iterator it = threadArgs->clients.begin(); it != threadArgs->clients.end(); ++it) {
                int sendEnd = write(*it, &buffer, sizeof(buffer));
                if (sendEnd == -1) {
                    throw "Error writing to socket";
                }
                close(*it);
                cout << "client" << *it << "is closed";
            }
            pthread_cancel(thread);
            close(serverSocket);
*/

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
    vector<pthread_t> threads;
    while (!stopServer) {
        cout <<"sizeV"<<threads.size();
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct
                sockaddr *) &clientAddress, &clientAddressLen);
        clients.push_back(clientSocket);
        handleClient.run(clientSocket);
    }
}



