#include <sys/socket.h>
#include "Command.h"
#include "HandleClient.h"

class StartCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
        games.insert(pair<string,int>(args[0],clientSocket1));
        cout << "Waiting for another client connections..." << endl;
        char approval[2] = {'1'};
        int sendApproval = send(clientSocket1, &approval[0], 1, 0);
        if (sendApproval < 0) {
            throw "error sending to client";
        }

    }
};
