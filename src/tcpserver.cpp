/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** server
*/

#include "../include/server.hpp"

#include <boost/asio.hpp>
using namespace saturnity;

void TcpServer::createSocket()
{
    boost::asio::io_service io_service;

    // listen for new connection
    boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234));

    // socket creation
    boost::asio::ip::tcp::socket socket_(io_service);
    acceptor_.accept(socket_);

    while (1) {
        // waiting for connection

        // read operation
        //        std::string message = read(socket_);
        //        std::cout << message << std::endl;
        // write operation
        char temp[50];
        std::cin >> temp;
        boost::asio::write(socket_, boost::asio::buffer(temp));
    }
    return 0;
}

bool TcpServer::handshake()
{
    return 1;
}

void TcpServer::receive() {}

void TcpServer::send(Packet toSend) {}
