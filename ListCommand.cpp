#include "Command.h"
#include "HandleGame.h"
#include <iostream>
using namespace std;

class ListCommand: public Command {
    virtual void execute(vector<string> args, int clientSocket1,int clientSocket2, map<string,int> &games) {
        cout << "Games avaliable to play are:\n";
        for(map<string,int>::iterator it = games.begin(); it != games.end(); ++it) {
            cout << it->first << "\n";
        }
    }
};