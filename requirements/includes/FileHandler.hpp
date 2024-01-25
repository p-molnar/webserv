#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include "httpRequest.hpp"
#include "httpResponse.hpp"


void    handleGetRequest(const httpRequest *req, httpResponse *res);

class fileHandler {
    public:
        static bool         fileExists(std::string& filePath);
        static std::string  readFileContent(const std::string& filePath);
        
    private:


};

#endif