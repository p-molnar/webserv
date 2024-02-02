#include "WebServer.hpp"


int main(int argc, char *argv[])
{
    g_config = nullptr;
    try
    {
        Config config(argc, argv);
        g_config = &config;
        g_config->display(); // temp for testing
        WebServer server;
        server.startService();
    }
    catch (const std::exception &e)
    {
        Log::logMsg(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
