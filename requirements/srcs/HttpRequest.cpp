#include "HttpRequest.hpp"

HttpRequest::HttpRequest()
    : request_line_parse_status(INCOMPLETE),
      request_headers_parse_status(INCOMPLETE),
      request_msg_body_parse_status(INCOMPLETE)
{
}

HttpRequest::HttpRequest(const HttpRequest &obj)
    : request_line_parse_status(obj.request_line_parse_status),
      request_headers_parse_status(obj.request_headers_parse_status),
      request_msg_body_parse_status(obj.request_msg_body_parse_status),
      raw_request(obj.raw_request),
      uri_comps(obj.uri_comps),
      request_line(obj.request_line),
      request_headers(obj.request_headers),
      request_message_body(obj.request_message_body),
      form_data(obj.form_data)
{
}

HttpRequest HttpRequest::operator=(const HttpRequest &obj)
{
    request_line_parse_status = obj.request_line_parse_status;
    request_headers_parse_status = obj.request_headers_parse_status;
    request_msg_body_parse_status = obj.request_msg_body_parse_status;
    raw_request = obj.raw_request;
    uri_comps = obj.uri_comps;
    request_line = obj.request_line;
    request_headers = obj.request_headers;
    request_message_body = obj.request_message_body;
    form_data = obj.form_data;
    return *this;
}

HttpRequest::~HttpRequest(){};

std::string HttpRequest::getMessageBody() const
{
    return request_message_body;
}

std::string get_cgi_ext(std::string s)
{
    try
    {
        for (std::string ext : Config::getConfig().getLocations()["/cgi-bin"].getCgiExt())
        {
            if (s.find(ext) != NPOS)
                return ext;
        }
        return "";
    }
    catch (std::out_of_range &e)
    {
        return "";
    }
}

void HttpRequest::parseRequestUri(const std::string &uri)
{
    std::vector<std ::string> uri_comps_local = tokenize(uri, QSTR_SEP);

    // extract path
    if (uri_comps_local.size() == 1)
    {
        uri_comps.path = uri_comps_local[0];
    }

    // extract query string
    if (uri_comps_local.size() == 2)
    {
        uri_comps.path = uri_comps_local[0];
        uri_comps.query_str = uri_comps_local[1];
    }

    // generate www_path based on path
    std::string root = strip(Config::getConfig().getRoot(), "/");
    std::string default_landing_page = strip(Config::getConfig().getIndex(), "/");

    uri_comps.www_path = uri_comps.path == "/"
                             ? root + "/" + default_landing_page
                             : root + uri_comps.path;

    // determine if the requested cgi is accepted, and if so what type of cgi it is

    std::string cgi_ext;
    if ((cgi_ext = get_cgi_ext(uri_comps.path)) != "")
    {
        request_type = EXECUTABLE;

        // extract executable name
        for (std::string comp : tokenize(uri_comps.path, DIR_SEP))
        {
            if (comp.find(cgi_ext) != NPOS)
            {
                uri_comps.executable_name = comp;
                break;
            }
        }

        // extract path_info
        std::size_t qstr_sep_pos = uri.find(QSTR_SEP);
        std::size_t path_info_start = uri.find(uri_comps.executable_name) + uri_comps.executable_name.length();
        if (qstr_sep_pos != NPOS)
            uri_comps.path_info = uri.substr(path_info_start, qstr_sep_pos - path_info_start);
        else
            uri_comps.path_info = uri.substr(path_info_start);
    }
    else if (uri_comps.www_path.back() == '/')
        request_type = DIRECTORY;
    else
        request_type = RESOURCE;
}

bool HttpRequest::parseRequest(char *raw_request_data, std::size_t bytes_received)
{
    static std::size_t clrf_pos;
    static std::size_t dbl_clrf_pos;

    raw_request += std::string(raw_request_data, bytes_received);

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
        dbl_clrf_pos = raw_request.find(TWO_CRLF);
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
            std::size_t content_length = atoi(getHeaderComp("Content-Length").c_str());

            // if (content_length > config.allowedUploadSize)
            // throw file too large exception

            std::size_t msg_body_start = dbl_clrf_pos + TWO_CRLF.length();
            std::string raw_msg_body = raw_request.substr(msg_body_start);

            // std::cout << "exp content_lenght: " << content_length << '\n';
            // std::cout << "content_lenght: " << raw_msg_body.length() << '\n';

            if (content_length != raw_msg_body.length())
                request_msg_body_parse_status = INCOMPLETE;
            else
            {
                parseMessageBody(raw_msg_body);
                request_msg_body_parse_status = COMPLETE;
            }
        }
        catch (const std::out_of_range &e)
        {
            request_msg_body_parse_status = NA;
        }
    }
    return (request_line_parse_status == COMPLETE &&
            request_headers_parse_status == COMPLETE &&
            (request_msg_body_parse_status == NA ||
             request_msg_body_parse_status == COMPLETE));
}

void HttpRequest::parseRequestLine(const std::string &raw_request)
{

    std::vector<std::string> request_line_comps = tokenize(raw_request, SP);

    if (request_line_comps.size() != 3)
        throw std::runtime_error("request line parse error: '" + raw_request + "'");

    std::vector<std::string>::iterator curr_field = request_line_comps.begin();

    request_line["method"] = *curr_field++;
    request_line["request_uri"] = *curr_field++;
    parseRequestUri(request_line.at("request_uri"));
    request_line["http_version"] = *curr_field++;
}

void HttpRequest::parseMessageBody(const std::string &raw_request)
{
    if (request_headers.at("Content-Type").find("multipart/form-data") != NPOS)
    {
        form_data = FormData(raw_request, request_headers);
    }
}

void HttpRequest::parseHeaders(const std::string &raw_request_headers)
{

    std::vector<std::string> headers = tokenize(raw_request_headers, CRLF);

    for (size_t i = 0; i < headers.size(); i++)
    {
        if (headers[i].size() == 0)
            continue;

        std::vector<std::string> header_parts = tokenize(headers[i], HEADER_SEP, 1);
        if (header_parts.size() != 2)
            throw std::runtime_error("http header parse error on line: '" + headers[i] + "'");

        std::string key = header_parts[0];
        std::string value = header_parts[1];

        request_headers[key] = value;
    }
}

t_uri_comps HttpRequest::getUriComps() const
{
    return uri_comps;
}

std::string HttpRequest::getRequestLineComp(const std::string &key) const
{
    return request_line.at(key);
}

std::string HttpRequest::getHeaderComp(const std::string &key) const
{
    return request_headers.at(key);
}

void HttpRequest::printParsedContent() const
{
    if (this->isParsed() == false)
        return;

    std::cout << "\n\nPARSED CONTENT:\n"
              << std::endl;

    std::cout << "path: |" << uri_comps.path << "|" << '\n';
    std::cout << "www_path: |" << uri_comps.www_path << "|" << '\n';
    std::cout << "executable_name: |" << uri_comps.executable_name << "|" << '\n';
    std::cout << "path_info: |" << uri_comps.path_info << "|" << '\n';
    std::cout << "query_string: |" << uri_comps.query_str << "|" << '\n';
    std::cout << "request type: " << request_type << '\n';

    for (std::pair<std::string, std::string> line : request_line)
    {
        std::cout << line.first;
        std::cout << ": ";
        std::cout << line.second;
        std::cout << " ";
    }
    std::cout << '\n';

    for (std::pair<std::string, std::string> header : request_headers)
    {
        std::cout << header.first;
        std::cout << ": ";
        std::cout << header.second;
        std::cout << "\n";
    }

    std::cout << "\n\n";
    std::cout << request_message_body << '\n';
}

void HttpRequest::flushBuffers()
{
    request_line_parse_status = INCOMPLETE;
    request_headers_parse_status = INCOMPLETE;
    request_msg_body_parse_status = INCOMPLETE;
    request_type = UNDEF;

    raw_request.erase();
    request_message_body.erase();
    request_line.clear();
    request_headers.clear();
    uri_comps.path.erase();
    uri_comps.executable_name.erase();
    uri_comps.path_info.erase();
    uri_comps.query_str.erase();
}

bool HttpRequest::isParsed() const
{
    return (request_line_parse_status == COMPLETE &&
            request_headers_parse_status == COMPLETE &&
            (request_msg_body_parse_status == NA ||
             request_msg_body_parse_status == COMPLETE));
}

const FormData &HttpRequest::getFormDataObj() const
{
    return form_data;
}