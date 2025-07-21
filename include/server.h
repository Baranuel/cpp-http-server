#pragma once

#include <string>
#include <unordered_map>

class Server
{
    int port;
    int server_fd;

public:
    Server(int port);
    ~Server();

    void start();
    void stop();
    void get();

private:
    void setupSocket();
    void handleClient(int client_fd);
};