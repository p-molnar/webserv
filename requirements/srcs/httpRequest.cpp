#include "httpRequest.hpp"
#include "WebServer.hpp"

httpRequest::httpRequest()
    : request_line_parse_status(INCOMPLETE),
      request_headers_parse_status(INCOMPLETE),
      request_msg_body_parse_status(INCOMPLETE)
{
}

std::string httpRequest::getMessageBody() const
{
    return request_message_body;
}

bool httpRequest::parseRequest(char *request_buff)
{
    raw_request += request_buff;

    static std::size_t clrf_pos;
    static std::size_t dbl_clrf_pos;

    if (request_line_parse_status == INCOMPLETE)
    {
        clrf_pos = raw_request.find(CRLF);
        if (clrf_pos != std::string::npos)
        {
            std::string raw_request_line = raw_request.substr(0, clrf_pos);
            parseRequestLine(raw_request_line);
            request_line_parse_status = COMPLETE;
        }
    }

    if (request_headers_parse_status == INCOMPLETE)
    {
        dbl_clrf_pos = raw_request.find(DBL_CRLF);
        if (dbl_clrf_pos != std::string::npos)
        {
            std::string raw_headers = raw_request.substr(clrf_pos, dbl_clrf_pos - clrf_pos);
            parseHeaders(raw_headers);
            request_headers_parse_status = COMPLETE;
        }
    }

    if (request_line_parse_status == COMPLETE && request_headers_parse_status == COMPLETE)
    {
        try
        {
            std::size_t content_length = atoi(getHeader("Content-Length").c_str());
            std::size_t msg_body_start = dbl_clrf_pos + DBL_CRLF.length();
            std::string raw_msg_body = raw_request.substr(msg_body_start);

            if (content_length != raw_msg_body.length())
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
}

// duplicate function, it's the same as httpRequest::getRequestLine("method")
// std::string httpRequest::getMethod() const
// {
//     return _method;
// }

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

// duplicate function, identical to httpRequest::printParsedContent()
// void httpRequest::printRequest() const
// {
//     std::cout << "HTTP Request:" << std::endl;
//     std::cout << "Method: " << _method << std::endl;
//     std::cout << "Path: " << _path << std::endl;
//     std::cout << "HTTP Version: " << _httpVersion << std::endl;

//     std::cout << "Headers:" << std::endl;
//     for (const auto &header : _headers)
//     {
//         std::cout << header.first << ": " << header.second << std::endl;
//     }
// }

// Commenting out to mute the compiler
// bool httpRequest::isComplete(const std::string &recievedData)
// {
//     size_t headerEnd = recievedData.find(CRLF);
//     if (headerEnd == std::string::npos)
//         return false;

//     if (this->_method == "POST")
//     {
//         size_t contentLengthHeaderStart = recievedData.find("Content-Length:");
//         if (contentLengthHeaderStart != std::string::npos)
//         {
//             size_t contentLengthHeaderEnd = recievedData.find("\r\n", contentLengthHeaderStart);
//             std::string contentLengthValue = recievedData.substr(contentLengthHeaderStart + 15, contentLengthHeaderEnd - (contentLengthHeaderStart + 15));

//             size_t contentLength = std::stoi(contentLengthValue);
//             size_t bodyStart = headerEnd + 4;
//             size_t bodyLength = recievedData.length() - bodyStart;

//             return bodyLength >= contentLength;
//         }
//         return true;
//     }
// }