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

enum e_request_type
{
    UNDEF,
    RESOURCE,
    EXECUTABLE,
};

typedef struct s_uri_comps
{
    std::string path;
    std::string query_str;
    std::string executable_name;
    std::string path_info;
} t_uri_comps;

class httpRequest
{
private:
    e_parse_status request_line_parse_status;
    e_parse_status request_headers_parse_status;
    e_parse_status request_msg_body_parse_status;
    e_request_type request_type;

private:
    std::string raw_request;
    t_uri_comps uri_comps;
    std::map<std::string, std::string> request_line;
    std::map<std::string, std::string> request_headers;
    std::string request_message_body;

private:
    void parseRequestLine(const std::string &raw_request);
    void parseRequestUri(const std::string &uri);
    void parseHeaders(const std::string &raw_request);
    void parseMessageBody(const std::string &raw_request);

public:
    httpRequest();
    httpRequest(const httpRequest &obj);
    httpRequest operator=(const httpRequest &obj);
    ~httpRequest();

    bool parseRequest(char *request_buff);
    void flushBuffers();
    void printParsedContent() const;

public:
    std::string getRequestLineComp(const std::string &request_line_el) const;
    t_uri_comps getUriComps() const;
    std::string getHeaderComp(const std::string &header_name) const;
    std::string getMessageBody() const;
    bool isParsed() const;
};

std::ostream &operator<<(std::ostream &os, const httpRequest &obj);

#endif