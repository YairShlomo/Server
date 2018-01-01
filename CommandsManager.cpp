#include "CommandsManager.h"
#include "StartCommand.cpp"
#include "CloseCommand.cpp"
#include "PlayCommand.cpp"
#include "ListCommand.cpp"
#include "JoinCommand.cpp"
CommandsManager::CommandsManager(map<string,int> games):games(games) {
    commandsMap["start"] = new StartCommand();
    commandsMap["close"] = new CloseCommand();
    commandsMap["play"] = new PlayCommand();
    commandsMap["list_games"] = new ListCommand();
    commandsMap["join"] = new JoinCommand();
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