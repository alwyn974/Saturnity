/*
** EPITECH PROJECT, 2023
** TCPConnectionToClient.cpp
** File description:
** TCPConnectionToClient.cpp
*/

#include "saturnity/asio/tcp/TCPConnectionToClient.hpp"
#include "saturnity/core/network/server/AbstractServer.hpp"

sa::TCPConnectionToClient::TCPConnectionToClient(const std::shared_ptr<PacketRegistry> &packetRegistry, int id, boost::asio::io_context &ioContext) :
    ConnectionToClient(packetRegistry, id, nullptr),
    _ioContext(ioContext),
    _socket(ioContext)
{}

void sa::TCPConnectionToClient::send(sa::ByteBuffer &buffer) {}

void sa::TCPConnectionToClient::send(sa::AbstractPacket &packet) {}

void sa::TCPConnectionToClient::send(const std::shared_ptr<AbstractPacket> &packet)
{
    this->send(*packet);
}

void sa::TCPConnectionToClient::send(const std::unique_ptr<AbstractPacket> &packet)
{
    this->send(*packet);
}

void sa::TCPConnectionToClient::disconnect()
{
    std::shared_ptr<sa::ConnectionToClient> clientPtr = this->shared_from_this();
    this->server->onClientDisconnected(clientPtr);
}

void sa::TCPConnectionToClient::disconnect(const std::string &reason) {}
