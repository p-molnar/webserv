#include "httpRequest.hpp"
#include "WebServer.hpp"
#include <string>

httpRequest::httpRequest()
    : request_line_parse_status(INCOMPLETE),
      request_headers_parse_status(INCOMPLETE),
      request_msg_body_parse_status(INCOMPLETE)
{
}

std::vector<std::string> httpRequest::tokenize(const std::string &input, const std::string &delimiter, std::size_t max_count = -1)
{
    std::vector<std::string> tokens;
    std::string token;

    size_t count = 0;
    size_t pos = 0;
    size_t found;

    while ((found = input.find(delimiter, pos)) != std::string::npos && count < max_count)
    {
        token = input.substr(pos, found - pos);
        tokens.push_back(token);
        pos = found + delimiter.size();
    }

    token = input.substr(pos);
    if (!token.empty())
    {
        tokens.push_back(token);
    }

    return tokens;
}

std::string httpRequest::getMessageBody() const
{
    return request_message_body;
}

bool httpRequest::parseRequest(char *request_buff)
{
    raw_request += request_buff;

    if (request_line_parse_status == INCOMPLETE)
    {
        std::size_t clrf_pos = raw_request.find(CRLF);
        if (clrf_pos != std::string::npos)
        {
            std::string raw_request_line = raw_request.substr(0, clrf_pos);
            parseRequestLine(raw_request_line);
            request_line_parse_status = COMPLETE;
        }
    }

    if (request_headers_parse_status == INCOMPLETE)
    {
        std::size_t dbl_clrf_pos = raw_request.find(DBL_CRLF);
        if (dbl_clrf_pos != std::string::npos)
        {
            std::size_t first_line = raw_request.find(CRLF);
            std::string raw_headers = raw_request.substr(first_line, dbl_clrf_pos);
            parseHeaders(raw_headers);
            request_headers_parse_status = COMPLETE;
        }
    }

    if (request_line_parse_status == COMPLETE && request_headers_parse_status == COMPLETE)
    {
        try
        {
            std::size_t content_length = atoi(getHeader("Content-Length").c_str());
            std::size_t msg_body_start = raw_request.find(DBL_CRLF);
            std::string raw_msg_body = raw_request.substr(msg_body_start);
            std::size_t msg_body_length = raw_request.substr(msg_body_start).length() - DBL_CRLF.length();

            if (content_length == msg_body_length)
                request_msg_body_parse_status = INCOMPLETE;
            else
            {
                parseMessageBody(raw_msg_body);
                request_msg_body_parse_status = COMPLETE;
            }
        }
        catch (const std::exception &e)
        {
            request_msg_body_parse_status = NA;
        }
    }
    return (request_line_parse_status == COMPLETE &&
            request_headers_parse_status == COMPLETE &&
            (request_msg_body_parse_status == NA ||
             request_msg_body_parse_status == COMPLETE));
}

void httpRequest::parseRequestLine(const std::string &raw_request)
{

    std::vector<std::string> request_line_parts = tokenize(raw_request, SP);

    if (request_line_parts.size() != 3)
        throw std::runtime_error("request line parse error: '" + raw_request + "'");

    std::vector<std::string>::iterator curr_field = request_line_parts.begin();

    request_line["method"] = *curr_field++;
    request_line["request_uri"] = *curr_field++;
    request_line["http_version"] = *curr_field++;
}

void httpRequest::parseMessageBody(const std::string &raw_request)
{
    request_message_body = raw_request;
}

void httpRequest::parseHeaders(const std::string &raw_request_headers)
{

    std::vector<std::string> headers = tokenize(raw_request_headers, CRLF);

    for (size_t i = 0; i < headers.size(); i++)
    {
        if (headers[i].size() == 0)
            continue;

        std::vector<std::string> header_parts = tokenize(headers[i], ": ", 1);
        if (header_parts.size() != 2)
            throw std::runtime_error("http header parse error on line: '" + headers[i] + "'");

        std::string key = header_parts[0];
        std::string value = header_parts[1];

        request_headers[key] = value;
    }
}

std::string httpRequest::getRequestLine(const std::string &request_line_name) const
{
    return request_line.at(request_line_name);
}

std::string httpRequest::getHeader(const std::string &headerName) const
{
    return request_headers.at(headerName);
}

void httpRequest::printParsedContent() const
{
    std::map<std::string, std::string>::const_iterator it = request_line.begin();
    std::map<std::string, std::string>::const_iterator ite = request_line.end();

    while (it != ite)
    {
        std::cout << it->first;
        std::cout << ": ";
        std::cout << it->second;
        std::cout << " ";
        it++;
    }
    std::cout << '\n';

    it = request_headers.begin();
    ite = request_headers.end();

    while (it != ite)
    {
        std::cout << it->first;
        std::cout << ": ";
        std::cout << it->second;
        std::cout << "\n";
        it++;
    }

    std::cout << request_message_body << '\n';
}

void httpRequest::flushBuffers()
{
    request_line_parse_status = INCOMPLETE;
    request_headers_parse_status = INCOMPLETE;
    request_msg_body_parse_status = INCOMPLETE;

    raw_request.erase();
    request_message_body.erase();
    request_line.clear();
    request_headers.clear();
}