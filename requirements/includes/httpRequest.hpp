#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "WebServer.hpp"
#include <map>
/*  HTTP Request parser.
    Requirements:
        - A request should never hang forever - set a timeout for a request;
        - GET, POST, DELETE methods should be parsed;
            - For POST parse the 'Content-Length' header. 
 */

/* TO MAKE : Chunked data function
    save chunks with istream and append to requestText
 */

class httpRequest 
{
    private:
        std::string                         _method;
        std::map<std::string, std::string>  _headers;

        void parseHeaders(const std::string& headers);

    
    public:
        httpRequest(const std::string& requestText);
        void            parseRequest(const std::string& requestText);
        void            parseRequestLine(const std::string& line);

        std::string getMethod() const;
        std::string getHeader(const std::string& headerName) const;
};

#endif