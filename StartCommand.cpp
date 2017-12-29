#include "Command.h"
#include "HandleClient.h"
#include <iostream>
class StartCommand: public Command {
    virtual void execute(vector<string> args, int clientsocket1,int clientsocket2, std::map<string,int> &games) {
        games.insert(std::pair<string,int>(args[0],clientsocket1));
    }
};
