#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "WebServer.hpp"

/*  HTTP Request parser.
    Requirements:
        - A request should never hang forever - set a timeout for a request;
        - GET, POST, DELETE methods should be parsed;
            - For POST parse the 'Content-Length' header. 
 */

class httpRequest 
{
    private:
        std::string     _method;
        std::string     _hostname;
        std::string     _userAgent;
        std::string     _buff[1024];

        std::string     _contentType;

        // int             _contentlength;

        // bool            _keepAlive;
    
    public:
        httpRequest(const std::string& requestText);
        void            parseRequest(const std::string& requestText);
        std::string     parseRequestLine(std::string& line);
};

#endif