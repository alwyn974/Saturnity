/*
** EPITECH PROJECT, 2023
** TCPServer.hpp
** File description:
** TCPServer.hpp
*/

#ifndef SATURNITY_TCPSERVER_HPP
#define SATURNITY_TCPSERVER_HPP

#include <spdlog/sinks/stdout_color_sinks.h>
#include "saturnity/core/network/server/AbstractServer.hpp"

namespace sa {
    class TCPServer : public AbstractServer {
    public:
        static std::shared_ptr<TCPServer> create(
            const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0", uint16_t port = 2409)
        {
            return std::shared_ptr<TCPServer>(new TCPServer(packetRegistry, host, port));
        }

        void init() override;

        void run() override;

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

    private:
        explicit TCPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0", uint16_t port = 2409);
    };
} // namespace sa

#endif // SATURNITY_TCPSERVER_HPP
