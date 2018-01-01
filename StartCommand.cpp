#include <sys/socket.h>
#include <unistd.h>
#include "Command.h"
#include "HandleClient.h"

class StartCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
        games.insert(pair<string,int>(args[0],clientSocket1));
        char buffer[6]={"start"};
        int myCommandSize = sizeof(buffer);
        int sendMessage = write(clientSocket1, &buffer, myCommandSize);
        if (sendMessage == -1) {
            throw "Error writing to socket";
        }

    }
};
