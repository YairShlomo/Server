#include "Command.h"
#include "HandleGame.h"
#include <iostream>
#include <sys/socket.h>

using namespace std;

class JoinCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
        games.erase(args[0]);
        cout << "2 clients connected" << endl;
        char buffer[2] = {'1', '2'};
        int sendByte = send(clientSocket1, &buffer[0], 1, 0);
        if (sendByte < 0) {
            throw "error sending to client";
        }
        sendByte = send(clientSocket2, &buffer[1], 1, 0);
        if (sendByte < 0) {
            throw "error sending to client";
        }
        CommandsManager commandsManager(games);
        HandleGame handleGame(clientSocket1,clientSocket2, commandsManager);
        handleGame.handle();
    }
};