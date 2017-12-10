/*
Name:Yair Shlomo
ID: 308536150
Name:Gal Eini
ID: 305216962
*/
#include "Server.h"
#include <iostream>
#include <fstream>

using namespace std;
string getlineInput(string line);

int main() {
    string line,Numb,port,ipAdress;
    int portNumb;
    ifstream myfile("../serverInfo.txt");
    int i = 0;
    if (myfile.is_open()) {
        getline(myfile, line);
        port = getlineInput(line);
        portNumb =atoi(port.c_str());

    } else {
    cout << "Unable to open file";

    return 0;
    }
    Server server(portNumb);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}
string getlineInput(string line){
    string delimiter = ":";
    string token = line.substr(line.find(delimiter) + 1, line.find("\n"));
    return token;
}