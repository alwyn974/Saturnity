/*
** EPITECH PROJECT, 2023
** UDPClient.hpp
** File description:
** UDPClient.hpp
*/

#ifndef SATURNITY_UDPClient_HPP
#define SATURNITY_UDPClient_HPP

#include <spdlog/sinks/stdout_color_sinks.h>
#include <boost/asio.hpp>
#include <queue>
#include "saturnity/core/network/client/AbstractClient.hpp"

/**
 * @brief UDP client implementation.
 */
namespace sa {
    /**
     * @brief Implementation of a UDP client
     */
    class UDPClient : public AbstractClient {
    public:
        /**
         * @brief Create a new UDP client.
         * @param packetRegistry the packet registry.
         * @return the UDP client.
         */
        static std::shared_ptr<UDPClient> create(const std::shared_ptr<PacketRegistry> &packetRegistry)
        {
            return std::shared_ptr<UDPClient>(new UDPClient(packetRegistry));
        }

        /**
         * @brief Initialize the client.
         * Instantiate the connection and launch the ioContext.
         */
        void init() override;

        /**
         * @brief Connect the client to the server.
         * @param host the host.
         * @param port the port.
         */
        void connect(const std::string &host, uint16_t port) override;

        /**
         * @brief Disconnect the client from the server.
         */
        void disconnect() override;

        /**
         * @brief Send data to the server.
         * @param buffer the data.
         * @deprecated use send(AbstractPacket &packet) instead.
         */
        void send(ByteBuffer &buffer) override;

        /**
         * @brief Send a packet to the server.
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         * @throws ClientNotConnectedException if the client is not connected to the server.
         */
        void send(AbstractPacket &packet) override { AbstractClient::send(packet); }

        /**
         * @brief Send a packet to the server.
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         * @throws ClientNotConnectedException if the client is not connected to the server.
         */
        void send(const std::shared_ptr<AbstractPacket> &packet) override { AbstractClient::send(packet); }

        /**
         * @brief Send a packet to the server.
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         * @throws ClientNotConnectedException if the client is not connected to the server.
         */
        void send(const std::unique_ptr<AbstractPacket> &packet) override { AbstractClient::send(packet); }

        // void receive(int size);

    private:
        boost::asio::io_context _ioContext; /**< The asio io context */
        boost::asio::ip::udp::socket _socket; /**< The asio UDP socket */
        boost::asio::ip::udp::endpoint _endpoint; /**< The endpoints found by the resolver */
        std::queue<ByteBuffer> _sendQueue; /**< The queue of data to send */

        /**
         * @brief Create a new UDP client.
         * @param packetRegistry the packet registry.
         */
        explicit UDPClient(const std::shared_ptr<PacketRegistry> &packetRegistry);

        void readPacketHeader();

        void readPacketBody(uint16_t size);

        void onRead(boost::system::error_code &ec, std::size_t bytesTransferred);

        void asyncRead();
    };
} // namespace sa

#endif // SATURNITY_UDPClient_HPP
