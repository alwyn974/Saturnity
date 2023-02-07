/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** main
*/

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "server.hpp"
#include "ByteBuffer.hpp"
#include <spdlog/spdlog.h>

void handle_receive(const boost::system::error_code& error, char recv_buffer[10])
{
    if (error) { std::cerr << "ERROR ASYNC: " << error.message() << std::endl; }
    std::cout << "ASYNC HAVE: " << recv_buffer << " WITH LEN: " << strlen(recv_buffer) << std::endl;
}

int udpServer(boost::asio::io_context& ioCtx)
{
    try {
        boost::asio::ip::udp::socket socket(ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 25565));
        char recv_buffer[10];
        for (;;) {
            for (int i = 9; i > 0; i--) { recv_buffer[i] = '\0'; }
            boost::asio::ip::udp::endpoint remoteEndpoint;
        sa::ByteBuffer buffer(100);
        std::vector<byte_t>  toto = buffer.readBytes(8); // NOLINT
        for (auto &i : toto)
        std::cout << i;
            socket.async_receive_from(boost::asio::buffer(buffer.vector()), remoteEndpoint, [&](boost::system::error_code error, std::size_t len) {
                // std::cout << "Received: " << buffer.getBuffer() << " and size: " << len << std::endl;
                std::vector<byte_t>  toto = buffer.readBytes(8); // NOLINT
                for (auto &i : toto)
                    std::cout << i;
                socket.send_to(boost::asio::buffer(recv_buffer, len), remoteEndpoint);
            });

            ioCtx.run();
            socket.async_receive_from(boost::asio::buffer(recv_buffer), remoteEndpoint,
                                      boost::bind(&handle_receive, boost::asio::placeholders::error, recv_buffer));
        }
    } catch (std::exception& e) {
        std::cout << "ERROR" << std::endl;
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

int main()
{
    boost::asio::io_context ioContext;
    saturnity::UdpServer const server(ioContext, 25565);
    ioContext.run();
}
