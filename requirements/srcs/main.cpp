#include "WebServer.hpp"

int main(int argc, char *argv[])
{
    // config.display();	// temp for testing

    try
    {
        Config config(argc, argv);
        // config.display(); // temp for testing
        WebServer server(config);

        // no need to load a config file anymore, because it is a global class
        // and every function has access to it

        // server.loadConfig(config);
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
