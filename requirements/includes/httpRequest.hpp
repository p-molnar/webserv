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

    Is the request read entirely?? aka > check content length to bytes recieved. 
 */

class httpRequest 
{
    private:
        std::string                         _method;
        std::string                         _path;
        std::string                         _httpVersion;
        std::map<std::string, std::string>  _headers;

        void parseHeaders(const std::string& headers);

    
    public:
        httpRequest(const std::string& requestText);
        
        void            parseRequest(const std::string& requestText);
        void            parseRequestLine(const std::string& line);

        std::string getMethod() const;
        std::string getHeader(const std::string& headerName) const;

        bool isComplete(const std::string& recievedData);
        void printRequest() const;
};

#endif