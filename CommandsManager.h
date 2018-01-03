#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H



#include <map>
#include "Command.h"
class  ClientInfo;

class CommandsManager {
public:
    /**
    * instructor. initialize CommandsManager
    * @param games - map with: name of game -client socket who opened it.
    */
    CommandsManager(map<string,int> games);
    //destructor
    ~CommandsManager();
    /**
    * executeCommand create commandObj and call excute func
    * @param command - only kind of command
    * @param args - all the rest of the full command in a vector.
    * @param clientsocket1 - number of socket connection of client1
    * @param clientsocket1 - number of socket connection of client2.
    */
    void executeCommand(string command, vector<string> args, int clientsocket1,int clientsocket2);
private:
    //map of kind of command and its command obj
    map<string, Command*> commandsMap;
    // map with: name of game -client socket who opened it.
    map<string,int> games;

};

#endif /* CommandsManager_H_ */



