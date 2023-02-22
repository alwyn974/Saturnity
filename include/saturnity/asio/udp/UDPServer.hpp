/*
** EPITECH PROJECT, 2023
** UDPServer.hpp
** File description:
** UDPServer.hpp
*/

#ifndef SATURNITY_UDPSERVER_HPP
#define SATURNITY_UDPSERVER_HPP

#include <spdlog/sinks/stdout_color_sinks.h>
#include "saturnity/core/network/server/AbstractServer.hpp"

namespace sa {
    class UDPServer : public AbstractServer {
    public:
        static std::shared_ptr<UDPServer> create(
            const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0", uint16_t port = 2409)
        {
            return std::shared_ptr<UDPServer>(new UDPServer(packetRegistry, host, port));
        }

        void init() override;

        void start() override;

        void stop() override;

        void broadcast(AbstractPacket &packet, int idToIgnore) override;

        void broadcast(AbstractPacket &packet) override { AbstractServer::broadcast(packet); }

        void sendTo(int id, ByteBuffer &buffer) override;

        void sendTo(int id, AbstractPacket &packet) override { AbstractServer::sendTo(id, packet); }

        void sendTo(int id, const std::shared_ptr<AbstractPacket> &packet) override { AbstractServer::sendTo(id, packet); }

        void sendTo(int id, const std::unique_ptr<AbstractPacket> &packet) override { AbstractServer::sendTo(id, packet); }

        void disconnect(int id) override;

        void disconnect(int id, const std::string &reason) override;

        void disconnectAll() override;

        void receive();

    private:
        explicit UDPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0", uint16_t port = 2409);
        boost::asio::ip::udp::socket _socket;

    };
} // namespace sa

#endif // SATURNITY_UDPSERVER_HPP
