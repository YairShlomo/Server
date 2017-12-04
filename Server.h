

#ifndef UNTITLED_SERVER_H
class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    void handleClient(int clientSocket);
    int calc(int arg1, const char op, int arg2) const;
};
#define UNTITLED_SERVER_H

#endif //UNTITLED_SERVER_H
