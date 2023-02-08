//
// Created by chatdo on 08/02/23.
//
/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** server
*/

#include "saturnity/asio/udp/server.hpp"
#include "saturnity/asio/udp/packets/packets.hpp"
#include "saturnity/core/ByteBuffer.hpp"

using namespace saturnity;

std::list<std::string> split_str(size_t pos, std::string& s, std::string delimiter)
{
    std::string token;
    std::list<std::string> parsed;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        parsed.insert(parsed.cend(), token);
        //        std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
    }
    return parsed;
}

UdpServer::UdpServer(boost::asio::io_context& ioContext, int port) :
    _ioCtx(ioContext), _socket(ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _port(port), _clientCount(0)
{
    receive();
}

UdpServer::~UdpServer()
{
    _socket.close();
}

void UdpServer::createSocket(int port)
{
    try {
        boost::asio::ip::udp::socket socket(_ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

bool UdpServer::handshake()
{
    return 1;
}

//void UdpServer::receive()
//{
//    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,
//                               boost::bind(&UdpServer::handleReceive, this, boost::asio::placeholders::error));
//}

void UdpServer::receive()
{
//    EntitySpawnPacket spawn;
//    spawn.fromBytes(_recvBuffer);
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer, 16), _remoteEndpoint,
                               boost::bind(&UdpServer::handleReceive, this, boost::asio::placeholders::error));
}

void UdpServer::handleReceive(const boost::system::error_code& error)
{
    if (error) {
        std::cerr << "ERROR RECEIVE ASYNC: " << error.message() << std::endl;
    } else {
        sa::ByteBuffer buffer(this->_recvBuffer.data(), this->_recvBuffer.size());
        auto id = buffer.readUShort();
        buffer.readUShort(); // NOLINT
        static const auto factory = PacketFactory::getFactory();
        if (!factory->hasPacket(id))
            throw std::runtime_error("Aled packet not found");
        auto packetFactory = factory->getPacket(id);
        auto packet = packetFactory(buffer);

        broadcast(_remoteEndpoint, id, *packet);

//        if ((received.compare(std::string("Hey")) && (!isInList(_remoteEndpoint)))) {
//            addClient(_remoteEndpoint, _clientCount);
//            broadcast(_remoteEndpoint, received);
//        } else {
//            std::cout << "Handling: " << _recvBuffer.data() << "|" << std::endl;
//        }
    }
}

void UdpServer::send(std::string& input)
{
    _socket.async_send_to(boost::asio::buffer(input), _remoteEndpoint, boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error));
}

void UdpServer::send(boost::asio::ip::udp::endpoint remoteEndpoint, std::string& input)
{
    _socket.async_send_to(boost::asio::buffer(input, input.size()), remoteEndpoint, boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error));
}



//template<typename Packet>
//void UdpServer::send(Packet& packet, boost::asio::ip::udp::endpoint remoteEndpoint)
//{
//    sa::ByteBuffer buffer(128);
//    static const auto factory = PacketFactory::getFactory();
//    auto id = factory->getPacketId<Packet>();
//    if (!id.has_value())
//        throw std::runtime_error("aled");
//    buffer.writeUShort(id);
//    buffer.writeUShort(0);
//    packet.toBytes(buffer);
//    buffer.setWriterIndex(sizeof(std::uint16_t));
//    buffer.writeUShort(buffer.size() - (sizeof(std::uint16_t) * 2));
//    buffer.setWriterIndex(buffer.size());
//    _socket.async_send_to(boost::asio::buffer(buffer.getBuffer(), buffer.size()), remoteEndpoint, boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error));
//}

void UdpServer::handleSend(const boost::system::error_code& error)
{
    if (error) {
        std::cerr << "ERROR SEND ASYNC: " << error.message() << std::endl;
    } else {
        std::cout << "ASYNC SENT" << std::endl;
        receive();
    }
}


void UdpServer::broadcastAll(std::string& message)
{
    std::cout << "BROADCAST ALL" << std::endl;
    for (const auto& [key, remote] : _clientList) { send(remote, message); }
    receive();
}

bool UdpServer::isInList(const boost::asio::ip::udp::endpoint newEndpoint)
{
    for (const auto& item : _clientList) {
        if (item.second == newEndpoint) { return true; }
    }
    return false;
}

void UdpServer::addClient(const boost::asio::ip::udp::endpoint newEndpoint, int id)
{
    _clientList[id] = newEndpoint;
    _clientCount++;
    // TODO: Check if exist
    showClients();
}

std::shared_ptr<PacketFactory> PacketFactory::_factory = nullptr;

// 1 SERVEUR, 2 CLIENTS SFML