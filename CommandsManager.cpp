#include "CommandsManager.h"
#include "StartCommand.cpp"

CommandsManager::CommandsManager() {
    commandsMap["start"] = new StartCommand();
// Add more commands...
}
void CommandsManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
}