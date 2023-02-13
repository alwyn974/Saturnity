#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "../include/server.hpp"

using boost::asio::ip::tcp;

int main() {

    saturnity::server::TCP server(saturnity::IPV::V4, 4242);

    server.onJoin = [](const saturnity::server::connection::TCP::Pointer& connection) {
        std::cout << "New connection from " << connection->getUsername() << std::endl;
    };

    server.onLeave = [](const saturnity::server::connection::TCP::Pointer& connection) {
        std::cout << "User has left the server: " << connection->getUsername() << std::endl;
    };

    server.onClientMessage = [&server](const std::string& message) {
        server.broadcast(message);
    };

    server.run();



    return 0;
}