#pragma once

class Server
{
    int port;
    int server_fd;

public:
    Server(int port);
    ~Server();

    void start();
    void stop();

private:
    void setupSocket();
    void handleClient(int client_fd);
};