#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"


void    handleGetRequest(const HttpRequest *req, HttpResponse *res);

class fileHandler {
    public:
        static bool         fileExists(std::string& filePath);
        static std::string  readFileContent(const std::string& filePath);
        
    private:


};

#endif