

#include <unistd.h>
#include <cstring>
#include <sstream>
#include "HandleGame.h"
#include "HandleClient.h"
HandleGame::HandleGame(int clientSocket1,int clientSocket2,CommandsManager commandsManager):
        clientSocket1(clientSocket1),clientSocket2(clientSocket2),commandsManager(commandsManager){
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
    char buffer[100];
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
        //n = read(currentSocket, &buffer, sizeof(buffer));
        vector<string> tokens = getCommand(currentSocket,command,buffer);
        if (n == -1) {
            cout << "Error reading" << endl;
            return;
        }
        if (n == 0) {
            char finish[7] = "ENDC";
            int clientEnd = write(otherSocket, &finish, sizeof(buffer));
            if (clientEnd == -1) {
                throw "Error writing to socket";
            }
            cout << "Client disconnected" << endl;
            return;
        }
        if (strcmp(buffer, "End") == 0) {
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


        commandsManager.executeCommand(command,tokens,clientInfo1,clientInfo2);
        n = write(otherSocket, &buffer, sizeof(buffer));
        if (n == -1) {
            throw "Error writing to socket";
        }
        turn = !turn;
    }
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