/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** client
*/

#include "client.hpp"
#include <thread>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace saturnity;

UdpClient::UdpClient(std::string address, std::string port, boost::asio::io_context& ioContext) :
    _address(address), _port(port), _ioContext(ioContext), _resolver(ioContext), _query(boost::asio::ip::udp::v4(), address, port), _socket(ioContext)
{
    _remoteEndpoint = boost::asio::ip::udp::endpoint(*_resolver.resolve(_query));
    _socket.open(boost::asio::ip::udp::v4());

    get_input();
    receive();
}

UdpClient::~UdpClient()
{
    _socket.close();
}

void UdpClient::receive()
{
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,
                               boost::bind(&UdpClient::handleReceive, this, boost::asio::placeholders::error));
}

void UdpClient::handleReceive(const boost::system::error_code& error)
{
    if (error) {
        std::cout << "ERROR WRITING" << std::endl;
    } else {
        std::cout << "Got: " << _recvBuffer.data() << std::endl;
        receive();
    }
}

void UdpClient::send()
{
    _socket.async_send_to(boost::asio::buffer(_input, _input.size()), _remoteEndpoint,
                          boost::bind(&UdpClient::handleSend, this, boost::asio::placeholders::error));
}

void UdpClient::send(std::string msg)
{
    _socket.async_send_to(boost::asio::buffer(msg, _input.size()), _remoteEndpoint,
                          boost::bind(&UdpClient::handleSend, this, boost::asio::placeholders::error));
}

void UdpClient::send(std::vector<uint8_t> input)
{
    _socket.async_send_to(boost::asio::buffer(input), _remoteEndpoint,
                          boost::bind(&UdpClient::handleSend, this, boost::asio::placeholders::error));
}

void UdpClient::handleSend(const boost::system::error_code& error)
{
    if (error) {
        std::cout << "ERROR WRITING" << std::endl;
    } else {
        std::cout << "ASYNC SENT" << std::endl;
    }
}

void UdpClient::get_input() {
    std::thread in([&]() {
        std::vector<uint8_t> test;
        test.resize(100);
        while (1) {
            std::getline(std::cin, _input);
            if (_input == "exit")
                std::exit(0);
            test[0] = _input[0];
            send(test);
        }
    });
    in.detach();
}

int main(int ac, char** av)
{
    boost::asio::io_context ioContext;
    UdpClient client("10.106.1.238", "25565", ioContext);
    ioContext.run();
}