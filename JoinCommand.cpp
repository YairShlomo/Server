#include "Command.h"
#include "HandleGame.h"
#include <iostream>
using namespace std;

class JoinCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
        games.erase(args[0]);
        CommandsManager commandsManager(games);
        HandleGame handleGame(clientSocket1,clientSocket2, commandsManager);
        handleGame.handle();
    }
};