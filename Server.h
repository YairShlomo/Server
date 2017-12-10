/*
Name:Yair Shlomo
ID: 308536150
Name:Gal Eini
ID: 305216962
*/
#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H

class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    void handleClient(int clientSocket);
    void handleClients(int clientSocket1, int clientSocket2);
    int calc(int arg1, const char op, int arg2) const;
};

#endif //UNTITLED_SERVER_H
