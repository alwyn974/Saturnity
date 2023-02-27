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
#include <boost/asio.hpp>

namespace sa {
    class UDPServer : public AbstractServer {
    public:
        static std::shared_ptr<UDPServer> create(const std::shared_ptr<PacketRegistry> &packetRegistry,
            const std::string &host = "0.0.0.0", uint16_t port = 2409)
        {
            return std::shared_ptr<UDPServer>(new UDPServer(packetRegistry, host, port));
        }

        void init() override;

        void start() override;

        void stop() override;

        void broadcast(AbstractPacket &packet, int idToIgnore) override;

        void broadcast(AbstractPacket &packet) override { AbstractServer::broadcast(packet); }

        void sendTo(int id, const ByteBuffer &buffer) override;

        void sendTo(int id, AbstractPacket &packet) override { AbstractServer::sendTo(id, packet); }

        void sendTo(int id, const std::shared_ptr<AbstractPacket> &packet) override { AbstractServer::sendTo(id, packet); }

        void sendTo(int id, const std::unique_ptr<AbstractPacket> &packet) override { AbstractServer::sendTo(id, packet); }

        void disconnect(int id) override;

        void disconnect(int id, const std::string &reason) override;

        void disconnectAll() override;

        void receive();

        void run();

        /**
         * @brief Read data from the server.
         */
        void asyncRead();

        /**
         * @brief Read the packet header from the server.
         */
        void asyncReadPacketHeader();

        /**
         * @brief Read the packet body from the server.
         * @param packetId the packet id.
         * @param packetSize the packet size.
         */
        void asyncReadPacketBody(std::uint16_t packetId, std::uint16_t packetSize);

        /**
         * @brief Handle the data received from the server.
         * @param packetId the packet id.
         * @param buffer the data.
         */
        void handlePacketData(std::uint16_t packetId, ByteBuffer &buffer);

    private:
        explicit UDPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0",
                           uint16_t port = 2409);
        boost::asio::io_context _ioCtx;
        std::vector<byte_t> _recvBuffer;
        boost::asio::ip::udp::endpoint _remote;
        boost::asio::executor_work_guard<decltype(_ioCtx.get_executor())> _work{_ioCtx.get_executor()};
        boost::asio::ip::udp::socket _socket =
                boost::asio::ip::udp::socket(_ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
    };
} // namespace sa

#endif // SATURNITY_UDPSERVER_HPP
