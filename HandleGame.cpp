

#include <unistd.h>
#include <cstring>
#include <sstream>
#include <sys/socket.h>
#include "HandleGame.h"
#include "HandleClient.h"
HandleGame::HandleGame(int clientSocket1,int clientSocket2,CommandsManager* commandsManager):
        clientSocket1(clientSocket1),clientSocket2(clientSocket2),commandsManager(commandsManager){
}

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
        if (tokens[0].compare("END") == 0) {
            return;
        }
        if (tokens[0].compare("ENS") == 0) {
            close(currentSocket);
            return;
        }
    }
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