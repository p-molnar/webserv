#ifndef HTTPREQUEST__HPP
#define HTTPREQUEST__HPP

#include <map>
#include <cstdio>
#include <cstring>
#include <string>
#include "consts.hpp"
#include "tokenizer.hpp"

/*  HTTP Request parser.
    Requirements:
        - A request should never hang forever - set a timeout for a request;
        - GET, POST, DELETE methods should be parsed;
            - For POST parse the 'Content-Length' header.
 */

/* TO MAKE : Chunked data function
    save chunks with istream and append to requestText
 */

enum e_parse_status
{
    INCOMPLETE,
    COMPLETE,
    NA,
};

class httpRequest
{
private:
    e_parse_status request_line_parse_status;
    e_parse_status request_headers_parse_status;
    e_parse_status request_msg_body_parse_status;

private:
    std::string raw_request;
    std::map<std::string, std::string> request_line;
    std::map<std::string, std::string> request_headers;
    std::string request_message_body;

private:
    void parseRequestLine(const std::string &raw_request);
    void parseHeaders(const std::string &raw_request);
    void parseMessageBody(const std::string &raw_request);

public:
    httpRequest();

    bool parseRequest(char *request_buff);
    void flushBuffers();

    std::string getRequestLine(const std::string &request_line_el) const;
    std::string getHeader(const std::string &header_name) const;
    std::string getMessageBody() const;
    std::map<std::string, std::string> getHeaders() const {return request_headers;}
    void printParsedContent() const;
};

std::ostream &operator<<(std::ostream &os, const httpRequest &obj);

#endif