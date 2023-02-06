/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** client
*/

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
using namespace boost::asio;

void handle_write(const boost::system::error_code& error) {
    if (error) {
        std::cout << "ERROR WRITING" << std::endl;
    }
}

void write_serv(boost::asio::ip::udp::socket& msocket, boost::asio::ip::udp::endpoint &remote, std::string& input) {
    msocket.async_send_to(boost::asio::buffer(input, input.size()), remote, boost::bind(&handle_write, boost::asio::placeholders::error));
    //boost::asio::async_write(msocket, boost::asio::buffer("Test", 5), boost::asio::transfer_all(), boost::bind(&handle_write, boost::asio::placeholders::error));

}

void udpClient(std::string address, std::string port)
{
    setvbuf(stdout, nullptr, _IONBF, 0);

    try {
        boost::asio::io_service io_service;
        boost::asio::ip::udp::resolver resolver(io_service);
        boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), address, "25565");
        boost::asio::ip::udp::endpoint receiverEndpoint = *resolver.resolve(query);

        boost::asio::ip::udp::socket msocket(io_service);
        msocket.open(boost::asio::ip::udp::v4());

        while (1) {
            std::string input;
            std::cin >> input;
            write_serv(msocket, receiverEndpoint, input);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return;
}

int main(int ac, char** av)
{
    boost::asio::io_service io_service;
    udpClient("10.106.1.238", "25565");
    io_service.run();

//     tcp::socket tcpSocket = tcpClient("127.0.0.1", 1234);
//    while (1) {
//        std::string input;
//        std::cin >> input;
//        readTcp();
//         tcpSocket.send(input)
//    }
}