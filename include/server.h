#pragma once

#include <string>
#include <unordered_map>

struct HttpRequest
{
    std::string method;
    std::string path;
    std::string version;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

struct HttpResponse
{
    int status_code;
    std::string status_message;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

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
    HttpRequest parseRawRequest(const std::string &request);
};