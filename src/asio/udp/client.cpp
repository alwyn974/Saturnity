/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** client
*/

#include "saturnity/asio/udp/client.hpp"
#include "saturnity/core/ByteBuffer.hpp"

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
        std::cout << "[Received] - [" << _recvBuffer.data() << "]" << std::endl;
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

//template<typename Packet>
//void UdpClient::send(const std::shared_ptr<Packet>& packet)
//{
//    sa::ByteBuffer buffer(128);
//    buffer.writeUShort(0);
//    buffer.writeUShort(0);
//    packet.toBytes(buffer);
//    buffer.setWriterIndex(sizeof(std::uint16_t));
//    buffer.writeUShort(buffer.size() - (sizeof(std::uint16_t) * 2));
//    buffer.setWriterIndex(buffer.size());
//    _socket.async_send_to(boost::asio::buffer(buffer.vector(), buffer.size()), _remoteEndpoint, boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error));
//}

void UdpClient::handleSend(const boost::system::error_code& error)
{
    if (error) {
        std::cout << "ERROR WRITING" << std::endl;
    } else {
        std::cout << "[Sent]" << std::endl;
    }
}

void UdpClient::get_input()
{
    std::thread in([&]() {
        std::vector<uint8_t> test;
        test.resize(100);
        while (1) {
            std::getline(std::cin, _input);
            if (_input == "exit") std::exit(0);
            test[0] = _input[0];
            send(_input);
        }
    });
    in.detach();
}
