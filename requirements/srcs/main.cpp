#include "WebServer.hpp"

Config *Config::instance = nullptr; // singleton design pattern

int main(int argc, char *argv[])
{
    try
    {
        WebServer server;
        Config::get().parse(argc, argv);
        // Config config(argc, argv);
        // config.display(); // temp for testing
        // server.loadConfig();
        server.startService();
    }
    catch (const std::exception &e)
    {
        Log::logMsg(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
