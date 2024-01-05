#include "WebServer.hpp"

int main()
{
    try
    {
        WebServer server;

        server.loadConfig();
        server.startService();
    }
    catch (const std::exception &e)
    {
        Log::logMsg(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
