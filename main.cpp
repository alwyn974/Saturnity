/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** main
*/

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "server.hpp"

int udpServer()
{
    try {
        boost::asio::io_context io_context;
        boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 25565));
        boost::array<char, 10> recv_buffer;
        for (;;) {
            boost::asio::ip::udp::endpoint remote_endpoint;
            std::size_t len = socket.receive_from(boost::asio::buffer(recv_buffer), remote_endpoint);
            for(char c:recv_buffer) {
                std::cout << c << std::endl;
            }
        }
    } catch (std::exception(e)) {
        std::cout << "ERROR" << std::endl;
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

int main(void)
{
    udpServer();

    // saturnity::Server server = saturnity::Server();
    // server.createSocket();
}