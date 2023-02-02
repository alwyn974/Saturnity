/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** main
*/

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "server.hpp"
#include <boost/bind.hpp>

void handle_receive(const boost::system::error_code& error, char recv_buffer[10]) {
    if (error) {
        std::cerr << "ERROR ASYNC: " << error.message() << std::endl;
    }
    std::cout << "ASYNC HAVE: " << recv_buffer << " WITH LEN: " << strlen(recv_buffer) << std::endl;
}

int udpServer(boost::asio::io_context& ioCtx)
{
    try {
        boost::asio::ip::udp::socket socket(ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 25565));
        char recv_buffer[10];
//        std::cout << sizeof(recv_buffer) / sizeof(char) << std::endl;
        for (;;) {
            for (int i = 9; i > 0; i--) {
                recv_buffer[i] = '\0';
            }
            boost::asio::ip::udp::endpoint remoteEndpoint;

            socket.async_receive_from(boost::asio::buffer(recv_buffer), remoteEndpoint, [&] (boost::system::error_code error, std::size_t len) {
                std::cout << "Received: " << recv_buffer << " and size: " << len << std::endl;
                socket.send_to(boost::asio::buffer(recv_buffer, len), remoteEndpoint);
            });

//            socket.async_send_to(boost::asio::buffer(recv_buffer), remoteEndpoint, [&] (boost::system::error_code, std::size_t len) {
//                std::cout << "Sent: " << recv_buffer << std::endl;
//            });
            ioCtx.run();
            socket.async_receive_from(boost::asio::buffer(recv_buffer), remoteEndpoint, boost::bind(&handle_receive, boost::asio::placeholders::error, recv_buffer));
//            std::size_t len = socket.receive_from(boost::asio::buffer(recv_buffer), remote_endpoint);
//            std::cout << "NOT ASYNC HAVE: "<< recv_buffer << " WITH LEN: " << len << std::endl;
//            socket.send_to(boost::asio::buffer(recv_buffer), remote_endpoint);

        }
    } catch (std::exception& e) {
        std::cout << "ERROR" << std::endl;
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


int main()
{
    // UDP no class
//    boost::asio::io_context ioContext;
//    udpServer(ioContext);
//    ioContext.run();

    // UDP class
//    boost::asio::io_context ioContext;
    saturnity::UdpServer const server(25565);
//    ioContext.run();

    // TCP
//    saturnity::Server server = saturnity::Server();
//    server.createSocket();
}