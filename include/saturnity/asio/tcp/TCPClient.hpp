/*
** EPITECH PROJECT, 2023
** TCPClient.hpp
** File description:
** TCPClient.hpp
*/

#ifndef SATURNITY_TCPCLIENT_HPP
#define SATURNITY_TCPCLIENT_HPP

#include "saturnity/core/network/client/AbstractClient.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <boost/asio.hpp>

/**
 * @brief TCP client implementation.
 */
namespace sa {
    /**
     * @brief Implementation of a TCP client with boost::asio.
     * @throws sa::ex::IOContextDeadException if the ioContext is dead. (send & read)
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
         * @brief Instanciate the client
         */
        void init() override;

        /**
         * @brief Run the client. (blocking)
         * Run the ioContext.
         */
        void run() override;

        /**
         * @brief Connect the client to the server.
         * @param host the host.
         * @param port the port.
         * @throws std::out_of_range if the port is invalid
         */
        void connect(const std::string &host, uint16_t port) override;

        /**
         * @brief Disconnect the client from the server.
         */
        void disconnect() override { this->disconnect(false); };

        /**
         * @brief Disconnect the client from the server.
         * @param forced true if the disconnection is forced.
         */
        void disconnect(bool forced) override;

        /**
         * @brief Send data to the server.
         * @param buffer the data.
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         * @deprecated use send(AbstractPacket &packet) instead.
         */
        void send(const ByteBuffer &buffer) override;

        /**
         * @brief Send a packet to the server. (The send can be delayed, due to the queue system)
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         * @throws ClientNotConnectedException if the client is not connected to the server.
         */
        void send(AbstractPacket &packet) override { AbstractClient::send(packet); }

        /**
         * @brief Send a packet to the server. (The send can be delayed, due to the queue system)
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         * @throws ClientNotConnectedException if the client is not connected to the server.
         */
        void send(const std::shared_ptr<AbstractPacket> &packet) override { AbstractClient::send(packet); }

        /**
         * @brief Send a packet to the server. (The send can be delayed, due to the queue system)
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         * @throws ClientNotConnectedException if the client is not connected to the server.
         */
        void send(const std::unique_ptr<AbstractPacket> &packet) override { AbstractClient::send(packet); }

    private:
        boost::asio::io_context _ioContext; /**< The asio io context */
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _workGuard; /**< The asio work guard, to force the idle of ioContext */
        boost::asio::ip::tcp::socket _socket; /**< The asio tcp socket */
        boost::asio::ip::tcp::resolver::results_type _endpoints; /**< The endpoints found by the resolver */
        TSQueue<ByteBuffer> _sendQueue; /**< The queue of data to send */
        TSQueue<ByteBuffer> _receiveQueue; /**< The queue of data received */

        /**
         * @brief Create a new TCP client.
         * @param packetRegistry the packet registry.
         */
        explicit TCPClient(const std::shared_ptr<PacketRegistry> &packetRegistry);

        /**
         * @brief Send the data in the queue.
         */
        void asyncSend();

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
    };
} // namespace sa

#endif // SATURNITY_TCPCLIENT_HPP
