/*
Name:Yair Shlomo
ID: 308536150
Name:Gal Eini
ID: 305216962
*/
#include<sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Server.h"
using namespace std;
#define MAX_CONNECTED_CLIENTS 2
Server::Server(int port): port(port), serverSocket(0) {
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
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    struct sockaddr_in clientAddress2;
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    if (listen(serverSocket, MAX_CONNECTED_CLIENTS) < 0) {
        throw "Error listening to socket";
    }
    socklen_t clientAddressLen = sizeof(clientAddress);
    socklen_t clientAddressLen2 = sizeof(clientAddress);
    while (true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct
                sockaddr *) &clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket == -1) {
            throw "Error accepting client";
        }
        cout << "Waiting for another client connections..." << endl;
        char approval[2] = {'1'};
        int sendApproval = send(clientSocket, &approval[0], 1, 0);
        if (sendApproval < 0) {
            throw "error sending to client";
        }
        int clientSocket2 = accept(serverSocket, (struct
                sockaddr *) &clientAddress2, &clientAddressLen2);
        if (clientSocket2 == -1) {
            throw "Error accepting client";
        }
        cout << "2 clients connected" << endl;
        char buffer[2] = {'1', '2'};
        int sendByte = send(clientSocket, &buffer[0], 1, 0);
        if (sendByte < 0) {
            throw "error sending to client";
        }
        sendByte = send(clientSocket2, &buffer[1], 1, 0);
        if (sendByte < 0) {
            throw "error sending to client";
        }
        handleClients(clientSocket,clientSocket2);
    }
}

void Server::handleClients(int clientSocket1, int clientSocket2) {
    char buffer[7];
    int n, currentSocket, otherSocket;
    bool turn = true;
    while (true) {
        if(turn) {
            currentSocket = clientSocket1;
            otherSocket = clientSocket2;
        }
        else {
            currentSocket = clientSocket2;
            otherSocket = clientSocket1;
        }

        n = read(currentSocket, &buffer, sizeof(buffer));


        if (n == -1) {
            cout << "Error reading" << endl;
            return;
        }
        if (n == 0) {
            char finish[7] ="ENDC";
            int clientEnd = write(otherSocket,&finish,sizeof(buffer));
            if (clientEnd == -1) {
                throw "Error writing to socket";
            }
            cout <<"Client disconnected"<<endl;
            return;
        }
        if(strcmp(buffer,"End")==0) {
            close(clientSocket1);
            close(clientSocket2);
            close(serverSocket);
            return;
        }
        if(strcmp(buffer,"X")==0) {
            close(clientSocket1);
            close(serverSocket);
            return;
        }
        if(strcmp(buffer,"O")==0) {
            close(clientSocket2);
            close(serverSocket);
            return;
        }
        n = write(otherSocket,&buffer,sizeof(buffer));
        if (n == -1) {
            throw "Error writing to socket";
        }
        turn = !turn;
    }
}
