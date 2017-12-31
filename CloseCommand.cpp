#include <unistd.h>
#include "Command.h"
#include "HandleClient.h"

class CloseCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
        games.erase(args[0]);
        close(clientSocket1);
        close(clientSocket2);
    }
};
