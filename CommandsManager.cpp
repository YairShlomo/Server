#include "CommandsManager.h"
#include "StartCommand.cpp"

class  clientInfo;
CommandsManager::CommandsManager(map<string,int> games):games(games) {
    commandsMap["start"] = new StartCommand();
}
void CommandsManager::executeCommand(string command, vector<string> args, clientInfo* clientInfo1,clientInfo* clientInfo2) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args,clientInfo1,clientInfo2);
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}