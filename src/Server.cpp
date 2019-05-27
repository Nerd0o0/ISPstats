#include <iostream>
#include <stdio.h>
#include <string>
#include <signal.h>

#include "../handlers/include/Factory.h"
#include "../include/Server.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/ScopedLock.h>
#include <Poco/URI.h>
#include <Poco/StringTokenizer.h>
#include "../include/Logger.h"

void posix_death_signal(int);

int Server::main(const std::vector<std::string> &)
{
    try {
        signal(SIGSEGV, posix_death_signal);

        auto *parameters = new Poco::Net::HTTPServerParams();
        parameters->setTimeout(10000);
        parameters->setMaxQueued(100);
        parameters->setMaxThreads(2);
        Poco::Net::SocketAddress socket_address("127.0.0.1:8080");
        Poco::Net::ServerSocket socket;
        socket.bind(socket_address, true, false);
        Logger::GetLogger().information("Server start at " + socket_address.toString());
        socket.listen(100);

        Poco::Net::HTTPServer server(new handlers::Factory(), socket, parameters);
        server.start();

        waitForTerminationRequest();
        server.stopAll();
        socket.close();
        Logger::GetLogger().information("Server stop with exit code " + std::to_string(Application::EXIT_OK));
        return Application::EXIT_OK;
    }catch(Poco::Exception e){
        Logger::GetLogger().critical("Server stop with Poco Server Exception: " + std::string(e.what()));
    }catch(std::exception e){
        Logger::GetLogger().critical("Server stop with std Exception: " + std::string(e.what()));
    }
}
void posix_death_signal(int signum)
{
    std::cout<<"SIGSEGV"<<std::endl;
    signal(signum, SIG_DFL);
    exit(3);
}