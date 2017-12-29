#include "CommandsManager.h"
#include "StartCommand.cpp"

CommandsManager::CommandsManager(map<string,int> games):games(games) {
    commandsMap["start"] = new StartCommand();
}
void CommandsManager::executeCommand(string command, vector<string> args, int clientsocket1,int clientsocket2) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args,clientsocket1,clientsocket2, games);
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}