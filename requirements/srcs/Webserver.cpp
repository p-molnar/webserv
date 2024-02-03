#include "WebServer.hpp"
#include <stdexcept>
#include "ServerSocket.hpp"

WebServer::WebServer(){};

// void WebServer::loadConfig(Config *config_data)
// {
//     config = config_data;
// }

void WebServer::startService()
{

    std::vector<pid_t> pids;
    for (ServerBlock config : Config::get().getServers())
    {
        int port = config.getListenPort();
        int backlog = 10;

        pid_t pid = SysCall::fork();
        // pid_t pid = fork();
        if (pid == 0)
        {
            try
            {
                Config::setConfig(&config);
                std::shared_ptr<ServerSocket> server_socket = std::shared_ptr<ServerSocket>(new ServerSocket());
                Log::logMsg("Server started");
                server_socket->createSocket();
                server_socket->bindPort(port);
                server_socket->listenPort(backlog, port);
                poll_manager.addSocket(server_socket);
                server_sockets.push_back(server_socket);
                poll_manager.processEvents();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                exit(EXIT_FAILURE); // rewrite with another function
            }
        }
        else if (pid > 0)
            pids.push_back(pid);
        else
            throw std::runtime_error("fork error: " + STRERR);
    }

    int status;
    while (pids.size() > 0)
    {
        pid_t child_pid = SysCall::waitpid(-1, &status, 0);
        if (child_pid > 0)
        {
            if (WIFEXITED(status))
                Log::logMsg("Child process exit: " + std::to_string(WEXITSTATUS(status)));
            else
                Log::logMsg("Child process abnormal exit: " + std::to_string(child_pid));
            pids.pop_back();
        }
    }
}

WebServer::~WebServer()
{
    Log::logMsg("Server(s) shutdown");
}
