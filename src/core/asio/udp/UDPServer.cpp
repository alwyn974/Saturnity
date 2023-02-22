/*
** EPITECH PROJECT, 2023
** UDPServer.cpp
** File description:
** UDPServer.cpp
*/

#include "saturnity/asio/udp/UDPServer.hpp"

namespace sa {
    sa::UDPServer::UDPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host, uint16_t port) :
            AbstractServer(packetRegistry, host, port)
    {
        // TODO: Implement UDP Server initialisation
        // TODO: add _socket and needed variables for server, and implement receive and send
        this->logger = *spdlog::stdout_color_mt("UDPServer");
    }

//    void sa::UDPServer::receive() {
//        _socket.async_receive_from(boost::asio::buffer(_recvBuffer, 16), _remoteEndpoint,
//                                   boost::bind(&UdpServer::handleReceive, this, boost::asio::placeholders::error));
//    }

    void sa::UDPServer::init()
    {
        this->logger.info("Initializing UDP server");
    }

    void sa::UDPServer::start() {}

    void sa::UDPServer::stop() {}

    void sa::UDPServer::broadcast(AbstractPacket &packet, int idToIgnore)
    {
        for (const auto &[id, con] : this->connections) {
            if (idToIgnore != -1 && idToIgnore == id) continue;
            sendTo(id, packet);
        }
    }

    void sa::UDPServer::sendTo(int id, ByteBuffer &buffer)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to send data to a non-existing connection (id: {})", id);
            return;
        }
        // TODO: Implement
        if (this->onServerDataSent) this->onServerDataSent(this->connections[id], buffer);
    }

    void sa::UDPServer::disconnect(int id)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to disconnect a non-existing connection (id: {})", id);
            return;
        }
        // TODO: Implement
        if (this->onServerDisconnected) this->onServerDisconnected(this->connections[id]);
        this->connections.erase(id);
    }

    void sa::UDPServer::disconnect(int id, const std::string &reason)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to disconnect a non-existing connection (id: {})", id);
            return;
        }
        this->connections[id]->disconnect(reason);
    }

    void sa::UDPServer::disconnectAll()
    {
        for (const auto &[id, con] : this->connections) {
            con->disconnect();
        }
    }
} // namespace sa
