
#ifndef COMMAND_H_
#define COMMAND_H_
#include <vector>
#include <string>
using namespace std;
class Command {
public:
    virtual void execute(vector<string> args) = 0;
    virtual ~Command() {}
};
#endif /* COMMAND_H_ */
