#ifndef HTTPREQUEST__HPP
#define HTTPREQUEST__HPP

#include <map>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

#include "consts.hpp"
#include "string_utils.hpp"
#include "FormData.hpp"
#include "Config.hpp"

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
    DIRECTORY,
    EXECUTABLE,
};

typedef struct s_uri_comps
{
    std::string path;
    std::string www_path;
    std::string query_str;
    std::string executable_name;
    std::string path_info;
} t_uri_comps;

class HttpRequest
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
    FormData form_data;

public:
    HttpRequest();
    HttpRequest(const HttpRequest &obj);
    HttpRequest operator=(const HttpRequest &obj);
    ~HttpRequest();

public:
    bool parseRequest(char *request_buff, std::size_t parse_size);
    void flushBuffers();
    void printParsedContent() const;

private:
    void parseRequestLine(const std::string &raw_request);
    void parseRequestUri(const std::string &uri);
    void parseHeaders(const std::string &raw_request);
    void parseMessageBody(const std::string &raw_request);
    std::string getCgiExtension(const std::string &s);
    void parseRequestType();
    std::string getExecutableName(const std::string &file_extension, const std::string &path);

public:
    std::string getRequestLineComp(const std::string &request_line_el) const;
    t_uri_comps getUriComps() const;
    std::string getHeaderComp(const std::string &header_name) const;
    std::string getMessageBody() const;
    e_request_type getType() const;
    const FormData &getFormDataObj() const;
    bool isParsed() const;
};

std::ostream &operator<<(std::ostream &os, const HttpRequest &obj);

#endif