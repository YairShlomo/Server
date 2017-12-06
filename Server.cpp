//#include <bits/socket_type.h>
#include<sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Server.h"


using namespace std;
#define MAX_CONNECTED_CLIENTS 2
/*
struct sockaddr {
        unsigned short sa_family;
        char sa_data[14];
};
struct sockaddr_in {
        short int sin_family;
        unsigned short int sin_port;
        struct in_addr sin_addr;
        unsigned char sin_zero[8];
};
*/
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
        int clientSocket2 = accept(serverSocket, (struct
                sockaddr *) &clientAddress2, &clientAddressLen2);
        if (clientSocket2 == -1) {
            throw "Error accepting client";
        }
        cout << "two clients are connected" << endl;
        //handleClient(clientSocket);
// Close communication with the client


        char buffer[2] = {'1', '2'};
        //buffer[0] =  '1';
        //buffer[1] =  '2';
        //int expectedDataLength = sizeof(buffer);



////////////////////////////////////////////////////
        //  int readByte=recv(clientSocket,buffer,expectedDataLength,0);

        // if (readByte==0) {
        //   throw "connection is closed";

        //} else if (readByte<=0) {
        //   throw "no receive";
        //  }
        //else {

        // cout << buffer;
        //  }

        int sendByte = send(clientSocket, &buffer[0], 1, 0);
        if (sendByte < 0) {
            throw "error sending to client";
        }
        sendByte = send(clientSocket2, &buffer[1], 1, 0);
        if (sendByte < 0) {
            throw "error sending to client";
        }


    }
    //close(clientSocket);

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

        n = read(currentSocket, buffer, sizeof(buffer));
        if (n == -1) {
            cout << "Error reading" << endl;
            return;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        if(buffer=="End") {
            close(serverSocket);
            return;
        }
        n = send(otherSocket,buffer,sizeof(buffer),0);
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        turn = !turn;
    }
}
// Handle requests from a specific client
void Server::handleClient(int clientSocket) {
    int arg1, arg2, n;
    char op;
    n = read(clientSocket, &arg2, sizeof(arg2));
    if (n == -1) {
        cout << "Error reading arg2" << endl;
        return;
    }
    while (true) {
// Read new exercise arguments
        int n = read(clientSocket, &arg1, sizeof(arg1));
        if (n == -1) {
            cout << "Error reading arg1" << endl;
            return;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        n = read(clientSocket, &op, sizeof(op));
        if (n == -1) {
            cout << "Error reading operator" << endl;
            return;
        }
        cout << "Got exercise: " << arg1 << op << arg2 << endl;
        int result = calc(arg1, op, arg2);
// Write the result back to the client
        n = write(clientSocket, &result, sizeof(result));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
    }
}
void Server::stop() {
    close(serverSocket);
}


int Server::calc(int arg1, const char op, int arg2) const {
    switch (op) {
        case '+':
            return arg1 + arg2;
        case '-':
            return arg1 - arg2;
        case '*':
            return arg1 * arg2;
        case '/':
            return arg1 / arg2;
        default:
            cout << "Invalid operator" << endl;
            return 0;
    }
}


