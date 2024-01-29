#include "WebServer.hpp"

int main(int argc, char* argv[])
{
	Config config(argc, argv);
	config.display();	// temp for testing

    try
    {
        WebServer server;

        server.loadConfig(config);
        server.startService();
    }
    catch (const std::exception &e)
    {
        Log::logMsg(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
