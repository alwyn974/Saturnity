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
    {
        this->logger = *spdlog::stdout_color_mt("TCPServer");
    }

    void sa::TCPServer::init()
    {
        this->logger.info("Initializing TCP server");
    }

    void sa::TCPServer::start() {}

    void sa::TCPServer::stop() {}

    void sa::TCPServer::broadcast(AbstractPacket &packet, int idToIgnore)
    {
        for (const auto &[id, con] : this->connections) {
            if (idToIgnore != -1 && idToIgnore == id) continue;
            sendTo(id, packet);
        }
    }

    void sa::TCPServer::sendTo(int id, ByteBuffer &buffer)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to send data to a non-existing connection (id: {})", id);
            return;
        }
        // TODO: Implement
        if (this->onServerDataSent) this->onServerDataSent(this->connections[id], buffer);
    }

    void sa::TCPServer::disconnect(int id)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to disconnect a non-existing connection (id: {})", id);
            return;
        }
        // TODO: Implement
        if (this->onServerDisconnected) this->onServerDisconnected(this->connections[id]);
        this->connections.erase(id);
    }

    void sa::TCPServer::disconnect(int id, const std::string &reason)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to disconnect a non-existing connection (id: {})", id);
            return;
        }
        this->connections[id]->disconnect(reason);
    }

    void sa::TCPServer::disconnectAll()
    {
        for (const auto &[id, con] : this->connections) {
            con->disconnect();
        }
    }
} // namespace sa
