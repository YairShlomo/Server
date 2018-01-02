#include <unistd.h>
#include <cstring>
#include "Command.h"
#include "HandleClient.h"

class PlayCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
        int n;
        if(args[0]=="End") {
            close(clientSocket1);
            close(clientSocket2);
        }
        else {


            for(vector<string>::iterator it = args.begin(); it != args.end(); ++it) {
                string k=*it;
                //char buffer[sizeof(k.c_str())+1];
                char buffer[2];

                strcpy(buffer,k.c_str());
                cout << buffer << "\n";

                int sendByte = write(clientSocket2, &buffer, sizeof(buffer));
                if (sendByte < 0) {
                    throw "error sending to client";
                }
            }
            char bufferEnd[7] = {"S"};
            int  sendByte = write(clientSocket2, &bufferEnd, 1);
            if (sendByte < 0) {
                throw "error sending to client";
            }
            /*
            //args.erase(args.begin());
            n = write(clientSocket2,&args,sizeof(args));
            if (n == -1) {
                throw "Error writing to socket";
            }
             */
        }
    }
};

