#include "httpRequest.hpp"
#include "WebServer.hpp"
#include "Log.hpp"
#include <string>
#include "consts.hpp"

httpRequest::httpRequest(const std::string& requestText)
{
    try {
        parseRequest(requestText);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error parsing HTTP request: " << e.what() << std::endl;
        throw;
    }
    printRequest();
}

void    httpRequest::parseRequest(const std::string& requestText)
{
    size_t firstline = requestText.find("\r\n");
    if (firstline == std::string::npos) {
        throw std::runtime_error("Invalid request line");
    }
    if (firstline != std::string::npos)
    {
        parseRequestLine(requestText.substr(0, firstline));
        std::string headersText = requestText.substr(firstline + 2);
        parseHeaders(headersText);
    }
}

void httpRequest::parseRequestLine(const std::string& line) 
{
    size_t firstSpace = line.find(' ');
    if (firstSpace == std::string::npos || firstSpace == 0) {
        throw std::runtime_error("Invalid request line: Method not found");
    }
    this->_method = line.substr(0, firstSpace);

    size_t secondSpace = line.find(' ', firstSpace + 1);
    if (secondSpace == std::string::npos) {
        this->_path = line.substr(firstSpace + 1);
        this->_httpVersion = "";
    } else {
        this->_path = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
        this->_httpVersion = line.substr(secondSpace + 1);
    }
    if (this->_path.empty()) {
        this->_path = "/";
    }
}



void    httpRequest::parseHeaders(const std::string& headers)
{
    std::string::size_type start = 0;
    std::string::size_type end;

    while ((end = headers.find("\r\n", start)) != std::string::npos)
    {
        std::string line = headers.substr(start, end - start);
        std::string::size_type delimiter = line.find(':');
        // if (delimiter == std::string::npos) {
        //     throw std::runtime_error("Malformed header line: " + line);
        // }
        if (delimiter != std::string::npos)
        {
            std::string key = line.substr(0, delimiter);
            std::string value = line.substr(delimiter + 2);
            _headers[key] = value;
            // THROWS IMMEDIATE EXCEPTION HANDLE DUPLICATE HEADERS> ESPECIALLY IN CHUNCKS
            // if (_headers.find(key) != _headers.end()) {
            //     throw std::runtime_error("Duplicate headers");
            // }
        }
        start = end + 2;
    }
}

std::string httpRequest::getMethod() const
{
    return _method;
}

std::string httpRequest::getHeader(const std::string& headerName) const
{
    auto it = _headers.find(headerName);
    if (it != _headers.end())
        return it->second;
    return "";
}

void httpRequest::printRequest() const 
{
    std::cout << "HTTP Request:" << std::endl;
    std::cout << "Method: " << _method << std::endl;
    std::cout << "Path: " << _path << std::endl;
    std::cout << "HTTP Version: " << _httpVersion << std::endl;

    std::cout << "Headers:" << std::endl;
    for (const auto& header : _headers) {
        std::cout << header.first << ": " << header.second << std::endl;
    }
}

bool httpRequest::isComplete(const std::string& recievedData) 
{
    size_t headerEnd = recievedData.find(CRLF);
    if (headerEnd == std::string::npos)
        return false;
    
    if (this->_method == "POST")
    {
        size_t contentLengthHeaderStart = recievedData.find("Content-Length:");
        if (contentLengthHeaderStart != std::string::npos) {
            size_t contentLengthHeaderEnd = recievedData.find("\r\n", contentLengthHeaderStart);
            std::string contentLengthValue = recievedData.substr( contentLengthHeaderStart + 15, contentLengthHeaderEnd - (contentLengthHeaderStart + 15));
            
            size_t contentLength = std::stoi(contentLengthValue);
            size_t bodyStart = headerEnd + 4;
            size_t bodyLength = recievedData.length() - bodyStart;

            return bodyLength >= contentLength;
        }
        return true;
    }
}