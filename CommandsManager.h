#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H



#include <map>
#include "Command.h"
#include "HandleClient.h"

class CommandsManager {
public:
    CommandsManager(map<string,int> Games);
    ~CommandsManager();
    void executeCommand(string command, vector<string> args,clientInfo clientInfo);
private:
    map<string, Command *> commandsMap;
    map<string,int> games;

};

#endif /* CommandsManager_H_ */



