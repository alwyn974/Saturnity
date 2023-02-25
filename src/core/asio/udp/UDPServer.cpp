/*
** EPITECH PROJECT, 2023
** UDPServer.cpp
** File description:
** UDPServer.cpp
*/

#include <iostream>
#include "saturnity/asio/udp/UDPServer.hpp"

namespace sa {
    sa::UDPServer::UDPServer(const std::shared_ptr<PacketRegistry> &packetRegistry,
                             const std::string &host, uint16_t port) :
            AbstractServer(packetRegistry, host, port)
    {
        // TODO: Implement UDP Server initialisation
        // TODO: add _socket and needed variables for server, and implement receive and send
//        _socket = boost::asio::ip::udp::socket(_ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
        this->logger = *spdlog::stdout_color_mt("UDPServer");
    }

    void sa::UDPServer::receive() {

        // TODO: fix this, Print Receiving and Lambda (on first message) but dosn't recursive
        std::cout << "Receiving" << std::endl;
        _socket.async_receive_from(boost::asio::buffer(_recvBuffer, 18), _remote, [&](boost::system::error_code err, std::size_t len) {
            std::cout << "LAMBDA: " << len << std::endl;
            if (err) {
                std::cout << "ERROR: " << err.message() << std::endl;
            } else {
                std::cout << "Received data: " << _recvBuffer.data() << std::endl;
            }
            receive();
        });
    };

    void sa::UDPServer::init()
    {
        this->logger.info("Initializing UDP server");
        _ioCtx.run();
    }

    void sa::UDPServer::start() {
        receive();
    }

    void sa::UDPServer::run() {
        _ioCtx.poll();
    }

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
