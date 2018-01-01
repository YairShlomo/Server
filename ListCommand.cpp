#include "Command.h"
#include "HandleGame.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

using namespace std;

class ListCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
       /* cout << "Games avaliable to play are:\n";
        for(map<string,int>::iterator it = games.begin(); it != games.end(); ++it) {
            cout << it->first << "\n";
        }*/
        int sendByte;
        char listGame[11]={"list_games"};
        sendByte = write(clientSocket1, &listGame, sizeof(listGame));

        for(map<string,int>::iterator it = games.begin(); it != games.end(); ++it) {
            char buffer[sizeof(it->first.c_str())+1];
            strcpy(buffer,it->first.c_str());
            cout << buffer << "\n";

            sendByte = write(clientSocket1, &buffer, sizeof(buffer));
            if (sendByte < 0) {
                throw "error sending to client";
            }
        }
        char bufferEnd[2] = {"0"};
        sendByte = write(clientSocket1, &bufferEnd[0], 1);
        if (sendByte < 0) {
            throw "error sending to client";
        }
    }
};