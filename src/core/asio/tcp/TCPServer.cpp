/*
** EPITECH PROJECT, 2023
** TCPServer.cpp
** File description:
** TCPServer.cpp
*/

#include "saturnity/asio/tcp/TCPServer.hpp"

namespace sa {
    sa::TCPServer::TCPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host, uint16_t port) :
        AbstractServer(packetRegistry, host, port)
    {}

    void sa::TCPServer::init() {}

    void sa::TCPServer::start() {}

    void sa::TCPServer::stop() {}

    void sa::TCPServer::broadcast(AbstractPacket &packet, int idToIgnore)
    {
        for (const auto &[id, con] : this->connections) {
            if (idToIgnore != -1 && idToIgnore == id) continue;
            con->send(packet);
        }
    }

    void sa::TCPServer::sendTo(int id, ByteBuffer &buffer) {}

    void sa::TCPServer::disconnect(int id) {}

    void sa::TCPServer::disconnect(int id, const std::string &reason) {}

    void sa::TCPServer::disconnectAll() {}
} // namespace sa
