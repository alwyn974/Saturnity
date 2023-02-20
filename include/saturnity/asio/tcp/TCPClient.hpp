/*
** EPITECH PROJECT, 2023
** TCPClient.hpp
** File description:
** TCPClient.hpp
*/

#ifndef SATURNITY_TCPCLIENT_HPP
#define SATURNITY_TCPCLIENT_HPP

#include <spdlog/sinks/stdout_color_sinks.h>
#include <boost/asio.hpp>
#include <queue>
#include "saturnity/core/network/client/AbstractClient.hpp"

/**
 * @brief TCP client implementation.
 */
namespace sa {
    /**
     * @brief Implementation of a TCP client
     */
    class TCPClient : public AbstractClient {
    public:
        /**
         * @brief Create a new TCP client.
         * @param packetRegistry the packet registry.
         * @return the TCP client.
         */
        static std::shared_ptr<TCPClient> create(const std::shared_ptr<PacketRegistry> &packetRegistry)
        {
            return std::shared_ptr<TCPClient>(new TCPClient(packetRegistry));
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
        boost::asio::ip::tcp::socket _socket; /**< The asio tcp socket */
        boost::asio::ip::tcp::resolver::results_type _endpoints; /**< The endpoints found by the resolver */
        std::queue<ByteBuffer> _sendQueue; /**< The queue of data to send */

        /**
         * @brief Create a new TCP client.
         * @param packetRegistry the packet registry.
         */
        explicit TCPClient(const std::shared_ptr<PacketRegistry> &packetRegistry);

        void onRead(boost::system::error_code &ec, std::size_t bytesTransferred);

        void asyncRead();
    };
} // namespace sa

#endif // SATURNITY_TCPCLIENT_HPP
