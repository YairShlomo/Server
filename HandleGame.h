
#ifndef GAMEHANDLE_H
#define GAMEHANDLE_H


#include "HandleClient.h"

class HandleGame {
private:
    int clientSocket1;
    int clientSocket2;
    CommandsManager* commandsManager;

public:
    HandleGame(int clientSocket1,int clientSocket2,CommandsManager* commandsManager);
    /**
    * getCommand arranging full command and returns vec with all words of command without
     * the command type itself.
    * @param clientSocket - number of socket connection of first client in game.
    * @param otherSocket - number of socket connection of second client in game
    * @param command - full command
    * @return tokens - vector with all the rest of full command.
    */
    vector<string> getCommand(int clientSocket,int otherSocket,string &command);
    /**
    * handle call excutecommand func.
    */
    void handle();
};


#endif //GAMEHANDLE_H
