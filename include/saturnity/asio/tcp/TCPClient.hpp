/*
** EPITECH PROJECT, 2023
** TCPClient.hpp
** File description:
** TCPClient.hpp
*/

#ifndef SATURNITY_TCPCLIENT_HPP
#define SATURNITY_TCPCLIENT_HPP

#include "saturnity/core/network/AbstractClient.hpp"

namespace sa {
    class TCPClient : public AbstractClient {
    public:
        explicit TCPClient(const std::shared_ptr<PacketRegistry> &packetRegistry);

        void init() override;

        void connect(const std::string &host, uint16_t port) override;

        void disconnect() override;

        void send(ByteBuffer &buffer) override;

        void send(AbstractPacket &packet) override { AbstractClient::send(packet); }

        void send(const std::shared_ptr<AbstractPacket> &packet) override { AbstractClient::send(packet); }

        void send(const std::unique_ptr<AbstractPacket> &packet) override { AbstractClient::send(packet); }

    private:
    };
} // namespace sa

#endif // SATURNITY_TCPCLIENT_HPP
