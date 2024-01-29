#include "WebServer.hpp"

int main(int argc, char *argv[])
{
    try
    {
        Config config(argc, argv);
        config.display(); // temp for testing
        WebServer server;
        server.loadConfig(&config);
        server.startService();
    }
    catch (const std::exception &e)
    {
        Log::logMsg(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
