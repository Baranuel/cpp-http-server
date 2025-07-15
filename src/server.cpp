#include <iostream>
#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <memory>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

Server::Server(int port) : port(port), server_fd(-1) {};
Server::~Server()
{
    stop();
};

void Server::setupSocket()
{
    std::cout << "Starting a server" << std::endl;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        throw std::runtime_error("Failed to initialize server socket");
    }
    int option = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &option, 4) < 0)
    {
        throw std::runtime_error("Error setting options");
    }

    sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (const struct sockaddr *)&address, sizeof(address)) < 0)
    {
        throw std::runtime_error("Failed to bind to the socket");
    }

    if (listen(server_fd, 10))
    {
        throw std::runtime_error("Failed to listen");
    }

    std::cout << "Server listenning on port: " << port << std::endl;
};

void Server::start()
{
    setupSocket();
    while (true)
    {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0)
        {
            perror("Error Accepting client");
            continue;
        };
        std::cout << "Accepting Clients" << std::endl;
        handleClient(client_fd);
    }
}

void Server::stop()
{
    std::cout << "Server stopped" << std::endl;
    close(server_fd);
};

void Server::handleClient(int client_fd)
{
    char buffer[1024]; // Creating buffer in memory for the client request;

    recv(client_fd, buffer, sizeof(buffer), 0);
    std::cout << "Received client request" << std::endl;
    std::cout << buffer << std::endl;

    std::string html_content = "Hello";

    // Build response manually (no httplib needed)
    std::string http_response = "HTTP/1.1 200 OK\r\n"
                                "Content-Type: text/html\r\n"
                                "Content-Length: " +
                                std::to_string(html_content.length()) + "\r\n"
                                                                        "Connection: close\r\n"
                                                                        "\r\n" +
                                html_content;

    std::cout << "Parsing request " << std::endl;
    HttpRequest parsedRequest = parseRawRequest(buffer);

    send(client_fd, http_response.c_str(), http_response.length(), 0);

    close(client_fd);
}

HttpRequest Server::parseRawRequest(const std::string &request)
{
    HttpRequest http_request;

    std::vector<std::string> lines;
    std::string line;
    std::istringstream stream(request);

    std::cout << "Raw request:  " << request << std::endl;

    while (std::getline(stream, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        std::cout << "Line from getLine:  " << line << std::endl;
        lines.push_back(line);
    }

    if (lines.empty())
    {
        return http_request;
    }
    std::cout << "Lines[0]   " << lines[0] << std::endl;
    std::istringstream request_line(lines[0]);
    request_line >> http_request.method >> http_request.path >> http_request.version;

    // Extract Headers
    for (size_t i = 1; i < lines.size(); i++) // why is this size_t??
    {
        std::string line = lines[i];
        if (line.empty())
        {
            break;
        }

        std::cout << "Processing line:  " << lines[i] << std::endl;
        size_t colon_position = line.find(":");

        if (colon_position != std::string::npos)
        {
            std::cout << "Colon position:  " << colon_position << std::endl;
            std::string key = line.substr(0, colon_position);
            std::string value = line.substr(colon_position + 1);

            while (!value.empty() && value.front() == ' ')
            {
                value.erase(0, 1);
            }

            while (!value.empty() && value.back() == ' ')
            {
                value.pop_back();
            }

            http_request.headers[key] = value;
        }
    }

    std::cout << "Parsed method: " << http_request.method << std::endl;
    std::cout << "Parsed path: " << http_request.path << std::endl;
    std::cout << "Parsed version: " << http_request.version << std::endl;
    std::cout << "Parsed headers: " << std::endl;
    for (const auto &header : http_request.headers)
    {
        std::cout << header.first << ": " << header.second << std::endl;
    }

    // Parse the body of the request here

    return http_request;
}