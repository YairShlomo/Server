

#include <unistd.h>
#include <cstring>
#include <sstream>
#include <sys/socket.h>
#include "HandleGame.h"
#include "HandleClient.h"
HandleGame::HandleGame(int clientSocket1,int clientSocket2,CommandsManager* commandsManager):
        clientSocket1(clientSocket1),clientSocket2(clientSocket2),commandsManager(commandsManager){
    cout << clientSocket1;
    cout << clientSocket2;
    /*
    clientInfo1=new clientInfo();
    clientInfo1->clientSocket=clientSocket1;
    clientInfo1->handleClient=handleClient1;
    clientInfo2=new clientInfo();
    clientInfo2->clientSocket=clientSocket2;
    clientInfo1->handleClient=handleClient2;
     */
}
/*
void HandleGame::run() {
    /*
    pthread_t thread;
    //gameThreads.push_back(thread);

    int gT = pthread_create(&thread, NULL,  gate, (void *)this);
    if (gT) {
        cout << "Error:unable to create thread"<< gT<<endl;
        exit(-1);
    }
    //cout <<games[]

    }
/*
}

static void* HandleGame::gate(void* elm) {
HandleGame* handleGame = (HandleGame*)elm;
    handleGame->handle();
}
 */
void HandleGame::handle() {
    int n, currentSocket, otherSocket;
    bool turn = true;
    string command;
    while (true) {
        if (turn) {
            currentSocket = clientSocket1;
            otherSocket = clientSocket2;
        } else {
            currentSocket = clientSocket2;
            otherSocket = clientSocket1;
        }
        vector<string> tokens = getCommand(currentSocket, otherSocket, command);
        if (tokens[0].compare("ENDC") == 0) {
            close(currentSocket);
            close(otherSocket);
            return;
        }
        commandsManager->executeCommand(command, tokens, currentSocket, otherSocket);

        turn = !turn;
    }
/*
        n = recv(currentSocket, &buffer, sizeof(buffer),0);

       /* if (strcmp(buffer, "End") == 0) {
            close(clientSocket1);
            close(clientSocket2);
            //close(serverSocket);
            return;
        }
        if (strcmp(buffer, "X") == 0) {
            close(clientSocket1);
            //close(serverSocket);
            return;
        }
        if (strcmp(buffer, "O") == 0) {
            close(clientSocket2);
            //close(serverSocket);
            return;
        }


        /* n = write(otherSocket, &buffer, sizeof(buffer));
         if (n == -1) {
             throw "Error writing to socket";
         }
         */
}


vector<string> HandleGame::getCommand(int clientSocket,int otherSocket, string &command) {
    char buffer[100];
    vector<string> tokens;
    int n;
    n = read(clientSocket, &buffer, sizeof(buffer));

    if (n == -1) {
        throw "Error reading";
    }

    if (n == 0) {
        char finish[7] = "ENDC";
        int clientEnd = write(otherSocket, &finish, sizeof(buffer));
        if (clientEnd == -1) {
            throw "Error writing to socket";
        }
        cout << "Client disconnected" << endl;
        tokens.push_back("ENDC");
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