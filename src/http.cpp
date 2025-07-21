#include "http.h"
#include <sstream>
#include <iostream>
#include <vector>

HttpRequest::HttpRequest(const std::string &request)
{
    std::vector<std::string> lines;
    std::string line;
    std::istringstream stream(request);

    while (std::getline(stream, line))
    {
        std::cout << "Line from getLine:  " << line << std::endl;
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (!line.empty())
            lines.push_back(line);
    }

    if (lines.empty())
        return;

    std::istringstream request_line(lines[0]);
    request_line >> method >> path >> version; // Map first line to method, path, and version on the class;

    for (size_t i = 1; i < lines.size(); i++)
    {
        if (lines[i].empty())
            continue;

        auto pos = lines[i].find(":");

        if (pos == std::string::npos)
            continue;

        std::string key = lines[i].substr(0, pos);
        std::string val = lines[i].substr(pos + 1);

        headers[key] = std::move(val);
    }
}

std::string HttpResponse::serialize() const
{
    std::ostringstream out;
    out << "HTTP/1.1" << status << "OK\r\n";

    for (auto &h : headers)
    {
        out << h.first << ":" << h.second << "\r\n";
    }
    out << "\r\n";
    out << body;
    return out.str();
}
