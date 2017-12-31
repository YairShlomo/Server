#include "Command.h"
#include "HandleGame.h"
#include <iostream>
#include <cstring>
#include <boost/iostreams/write.hpp>

using namespace std;

class ListCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
       /* cout << "Games avaliable to play are:\n";
        for(map<string,int>::iterator it = games.begin(); it != games.end(); ++it) {
            cout << it->first << "\n";
        }*/
        char buffer[50];
        int sendByte;
        for(map<string,int>::iterator it = games.begin(); it != games.end(); ++it) {
            strcpy(buffer,it->first.c_str());
            sendByte = write(clientSocket1, &buffer, sizeof(buffer));
            if (sendByte < 0) {
                throw "error sending to client";
            }
        }
        buffer[0] = '0';
        sendByte = write(clientSocket1, &buffer[0], 1);
        if (sendByte < 0) {
            throw "error sending to client";
        }
    }
};