#include "WebServer.hpp"

Config *Config::instance = nullptr;           // singleton design pattern
ServerBlock *Config::server_config = nullptr; // singleton design pattern

int main(int argc, char *argv[])
{
	// Config config(argc, argv);
	// config.display();	// temp for testing

    try
    {
        WebServer server;
        Config::get().parse(argc, argv);
        Config::get().parseRedirect("redirects");

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
