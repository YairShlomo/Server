#include "CommandsManager.h"
#include "StartCommand.cpp"

CommandsManager::CommandsManager(map<string,int> games):games(games) {
    commandsMap["start"] = new StartCommand();
}
void CommandsManager::executeCommand(string command, vector<string> args, ClientInfo clientInfo) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}