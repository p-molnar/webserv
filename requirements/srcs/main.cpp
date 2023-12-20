#include "WebServer.hpp"
#include <iostream>
#include <vector>
#include <sys/socket.h>

int main()
{
    try
    {
        WebServer server;

        // server.loadConfig();
        server.startService();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
