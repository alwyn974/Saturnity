#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "../include/server.hpp"

using boost::asio::ip::tcp;

int main() {

    saturnity::server::TCP server(saturnity::IPV::V4, 4242);
    server.run();



    return 0;
}