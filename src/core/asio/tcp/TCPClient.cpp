/*
** EPITECH PROJECT, 2023
** TCPClient.cpp
** File description:
** TCPClient.cpp
*/

#include "saturnity/asio/tcp/TCPClient.hpp"

namespace sa {
    TCPClient::TCPClient(const std::shared_ptr<PacketRegistry> &packetRegistry) : AbstractClient(packetRegistry) {}

    void TCPClient::init() {}

    void TCPClient::connect(const std::string &host, uint16_t port)
    {
        // TODO: Implement
    }

    void TCPClient::disconnect() {}

    void TCPClient::send(ByteBuffer &buffer)
    {
        // TODO: Implement
    }
} // namespace sa
