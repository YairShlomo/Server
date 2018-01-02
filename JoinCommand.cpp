#include "Command.h"
#include "HandleGame.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

class JoinCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
        clientSocket2 =games.find(args[0])->second;
        if (games.find(args[0]) == games.end()) {
            char buffer[10] = {"bad name"};
            int sendMessage = write(clientSocket1, &buffer, 10);
            if (sendMessage == -1) {
                throw "Error writing to socket";
            }
        } else {
            games.erase(args[0]);
            cout << "2 clients connected" << endl;
            char buffer[2] = {'1', '2'};
            int sendByte = send(clientSocket2, &buffer[0], 1, 0);
            if (sendByte < 0) {
                throw "error sending to client";
            }
            sendByte = send(clientSocket1, &buffer[1], 1, 0);
            if (sendByte < 0) {
                throw "error sending to client";
            }
            CommandsManager* commandsManager=new CommandsManager(games);
            HandleGame handleGame(clientSocket2, clientSocket1, commandsManager);
            cout << clientSocket1;
            cout << clientSocket2;
            handleGame.handle();
        }
    }
};