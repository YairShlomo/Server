#include <unistd.h>
#include "Command.h"
#include "HandleClient.h"

class PlayCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
        int n;
        if(args[0]=="End") {
            close(clientSocket1);
            close(clientSocket2);
        }
        else{
            //args.erase(args.begin());
            n = write(clientSocket2,&args,sizeof(args));
            if (n == -1) {
                throw "Error writing to socket";
            }
        }
    }
};

