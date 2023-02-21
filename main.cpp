#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "../include/server.hpp"
#include <chrono>
#include <spdlog/spdlog.h>

using boost::asio::ip::tcp;

int main() {

    saturnity::server::TCP server(saturnity::IPV::V4, 2409);

    server.onJoin = [](const saturnity::server::connection::TCP::Pointer& connection) {
        std::cout << "New connection from " << connection->getUsername() << std::endl;
    };

    server.onLeave = [](const saturnity::server::connection::TCP::Pointer& connection) {
        std::cout << "User has left the server: " << connection->getUsername() << std::endl;
    };

    server.onClientMessage = [&](const std::string& message) {
        spdlog::info("Message received: {}", message);
    };

    std::thread t([&](){
      server.run();
    });
    t.detach();

    const int id = 0x01;
    const int size = 18;
    const int strSize = 12;

    const std::string message = { ((char *)(&id))[0], ((char *)(&id))[1], ((char *)(&size))[0], ((char *)(&size))[1], ((char *)(&strSize))[0], ((char *)(&strSize))[1], 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!' };

    while (true) {
        server.broadcast(message);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}