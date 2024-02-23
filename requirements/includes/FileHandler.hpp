#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"


void    handleGetRequest(const HttpRequest *req, HttpResponse *res);
void    handlePostRequest(const HttpRequest *req, HttpResponse *res);
void    handleDeleteRequest(const HttpRequest *req, HttpResponse *res);
std::string getContentType(const std::string &file_path);

class fileHandler {
    public:
        static bool         isValidPath(std::string& filePath);
        static std::string  readFileContent(const std::string& filePath);
        static bool         isDirectory(std::string& filePath);
        static bool         isFile(std::string& filePath);
        static bool         deleteResource(const std::string& file_path);
    private:


};

#endif