#pragma once

#include <string>
#include <unordered_map>

class HttpRequest
{
public:
    std::string method;
    std::string path;
    std::string version;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

public:
    HttpRequest() = default;
    HttpRequest(const std::string &request);
    ~HttpRequest() = default;

private:
    void parseHeaders(const std::string &request);
    void parseBody(const std::string &request);
};

class HttpResponse
{
public:
    int status = 0;
    std::string body;
    std::unordered_map<std::string, std::string> headers;
    std::string serialize() const;
};