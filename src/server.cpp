/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** server
*/

#include "../include/server.hpp"
#include <boost/asio.hpp>
using namespace saturnity;

std::string read_(boost::asio::ip::tcp::socket& socket)
{
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}

int Server::createSocket()
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
        std::string message = read_(socket_);
        std::cout << message << std::endl;
        // write operation
        char temp[50];
        std::cin >> temp;
        boost::asio::write(socket_, boost::asio::buffer(temp));
    }
    return 0;
}

bool Server::handshake() {

    return 1;
}

void Server::sendPacket(Packet toSend) {}

void Server::addPlayer() {}

void Server::disconnectPlayer() {}

void Server::movePlayer() {}
