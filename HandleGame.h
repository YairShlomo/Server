
#ifndef GAMEHANDLE_H
#define GAMEHANDLE_H


#include "HandleClient.h"

class HandleGame {
private:
    int clientSocket1;
    int clientSocket2;
    CommandsManager commandsManager;
    clientInfo* clientInfo1;
    clientInfo* clientInfo2;
public:
    HandleGame(int clientSocket1,int clientSocket2,CommandsManager commandsManager);
    //static void* gate(void* elm);
    vector<string> getCommand(int clientSocket,string &command,char* buffer);

        void handle();

    //void run();

};


#endif //GAMEHANDLE_H
