/*
** EPITECH PROJECT, 2023
** TCPServer.cpp
** File description:
** TCPServer.cpp
*/

#include "saturnity/asio/tcp/TCPServer.hpp"

namespace sa {
    TCPServer::TCPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host, uint16_t port) :
        AbstractServer(packetRegistry, host, port)
    {
        this->logger = *spdlog::stdout_color_mt("TCPServer");
    }

    void TCPServer::init()
    {
        this->logger.info("Initializing TCP server");
    }

    void TCPServer::run()
    {
        this->logger.info("Running TCP server");
    }

    void TCPServer::start() {}

    void TCPServer::stop() {}

    void TCPServer::broadcast(AbstractPacket &packet, int idToIgnore)
    {
        for (const auto &[id, con] : this->connections) {
            if (idToIgnore != -1 && idToIgnore == id) continue;
            sendTo(id, packet);
        }
    }

    void TCPServer::sendTo(int id, const ByteBuffer &buffer)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to send data to a non-existing connection (id: {})", id);
            return;
        }
        // TODO(alwyn974): Implement
        // if (this->onServerDataSent) this->onServerDataSent(this->connections[id], buffer);
    }

    void TCPServer::disconnect(int id)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to disconnect a non-existing connection (id: {})", id);
            return;
        }
        // TODO(alwyn974): Implement
        if (this->onServerDisconnected) this->onServerDisconnected(this->connections[id]);
        this->connections.erase(id);
    }

    void TCPServer::disconnect(int id, const std::string &reason)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to disconnect a non-existing connection (id: {})", id);
            return;
        }
        this->connections[id]->disconnect(reason);
    }

    void TCPServer::disconnectAll()
    {
        for (const auto &[id, con] : this->connections) {
            con->disconnect();
        }
    }
} // namespace sa
