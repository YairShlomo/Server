
#ifndef COMMAND_H_
#define COMMAND_H_
#include <vector>
#include <string>
#include <map>
using namespace std;
class Command {
public:
    virtual void execute(vector<string> args, int clientsocket1,int clientsocket2, std::map<string,int> &games) = 0;
    virtual ~Command() {}
};
#endif /* COMMAND_H_ */
