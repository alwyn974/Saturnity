/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** client
*/

#include "client.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace saturnity;

UdpClient::UdpClient(std::string address, std::string port, boost::asio::io_context& ioContext) :
    _address(address),
    _port(port),
    _ioContext(ioContext),
    _resolver(ioContext),
    _query(boost::asio::ip::udp::v4(), address, port),
    _socket(ioContext)
{
    _remoteEndpoint = boost::asio::ip::udp::endpoint(*_resolver.resolve(_query));
    _socket.open(boost::asio::ip::udp::v4());

    while (1) {
        std::cin >> _input;
        send();
        receive();
    }
}

UdpClient::~UdpClient()
{
    _socket.close();
}

void UdpClient::handleReceive(const boost::system::error_code& error, std::string& received)
{
    std::cout << "HANDLING" << std::endl;
    if (error) {
        std::cout << "ERROR WRITING" << std::endl;
    } else {
        std::cout << "Got: " << received << std::endl;
        receive();
    }
}

void UdpClient::receive()
{
    std::string received;
    std::cout << "READING" << std::endl;
    _socket.async_receive_from(boost::asio::buffer(received), _remoteEndpoint, boost::bind(&UdpClient::handleReceive, this, boost::asio::placeholders::error, received));
}

void UdpClient::handleSend(const boost::system::error_code& error)
{
    if (error) { std::cout << "ERROR WRITING" << std::endl; }
}

void UdpClient::send()
{
    _socket.async_send_to(boost::asio::buffer(_input, _input.size()), _remoteEndpoint, boost::bind(&UdpClient::handleSend, this, boost::asio::placeholders::error));
    // boost::asio::async_write(msocket, boost::asio::buffer("Test", 5), boost::asio::transfer_all(), boost::bind(&handle_write,
}


int main(int ac, char** av)
{
    boost::asio::io_context ioContext;
    UdpClient client("10.106.1.238", "25565", ioContext);
    ioContext.run();

}