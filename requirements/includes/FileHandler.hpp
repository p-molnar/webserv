/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FileHandler.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 11:59:28 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:03:23 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

/* C/C++ Libs */
#include <filesystem>
#include <iterator>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <cstdio>

/* Webserv */
#include "Log.hpp"
#include "HttpResponse.hpp"
#include "httpStatus.hpp"
#include "RequestProcessor.hpp"

class fileHandler {
    public:
        static bool         isValidPath(std::string& filePath);
        static std::filesystem::path getAbsolutePath(const std::string &file_path_input, const std::string &root_input);
        static std::string  readFileContent(const std::string& filePath);
        static bool         isDirectory(std::string& filePath);
        static bool         isFile(std::string& filePath);
        static bool         deleteResource(const std::string& file_path);
        static void         handleErrorResponse(int errorCode, const HttpRequest *req, HttpResponse *res);
        static void         serveStaticFile(const std::string& file_path, HttpResponse *res);
        static void         handleExecutableRequest(const HttpRequest *req, HttpResponse *res);
        static void         serveDirectoryListing(const HttpRequest *req, HttpResponse *res);
    private:


};

#endif