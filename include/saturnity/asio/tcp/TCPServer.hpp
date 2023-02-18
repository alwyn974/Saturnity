/*
** EPITECH PROJECT, 2023
** TCPServer.hpp
** File description:
** TCPServer.hpp
*/

#ifndef SATURNITY_TCPSERVER_HPP
#define SATURNITY_TCPSERVER_HPP

#include "saturnity/core/network/AbstractServer.hpp"

namespace sa {
    class TCPServer : public AbstractServer {
    public:
        explicit TCPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0", uint16_t port = 2409);

        void init() override;

        void start() override;

        void stop() override;

        void broadcast(AbstractPacket &packet, int idToIgnore) override;

        void broadcast(AbstractPacket &packet) override { AbstractServer::broadcast(packet); }

        void sendTo(int id, ByteBuffer &buffer) override;

        void disconnect(int id) override;

        void disconnect(int id, const std::string &reason) override;

        void disconnectAll() override;
    };
} // namespace sa

#endif // SATURNITY_TCPSERVER_HPP
