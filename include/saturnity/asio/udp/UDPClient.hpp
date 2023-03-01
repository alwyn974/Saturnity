/*
** EPITECH PROJECT, 2023
** UDPClient.hpp
** File description:
** UDPClient.hpp
*/

#ifndef SATURNITY_UDPCLIENT_HPP
#define SATURNITY_UDPCLIENT_HPP

#include "AbstractUDPProtocol.hpp"
#include "saturnity/core/network/client/AbstractClient.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <boost/asio.hpp>
#include <queue>

/**
 * @brief UDP client implementation.
 */
namespace sa {
    /**
     * @brief Implementation of a UDP client
     * By default the udp client will read only a maximum of 1024 bytes. @see AbstractUDPProtocol::setMaxBufferSize @endsee
     * @throws sa::ex::IOContextDeadException if the ioContext is dead. (send & read)
     */
    class UDPClient
        : public AbstractClient,
          public AbstractUDPProtocol {
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
         */
        void init() override;

        /**
         * @brief Run the client. (blocking)
         * Run the ioContext.
         * @throws sa::ex::AlreadyRunningException if the client is already running.
         */
        void run() override;

        /**
         * @brief Run the client asynchronously.
         * Run the ioContext in a thread.
         * @throws sa::ex::AlreadyRunningException if the client is already running.
         */
        void asyncRun();

        /**
         * @brief Stop the client.
         */
        void stop() override;

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
         * @deprecated use send(AbstractPacket &packet) instead.
         */
        void send(const ByteBuffer &buffer) override;

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

    private:
        boost::asio::io_context _ioContext; /**< The asio io context */
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _workGuard; /**< The asio work guard, to force the idle of ioContext */
        boost::asio::ip::udp::socket _socket; /**< The asio UDP socket */
        boost::asio::ip::udp::resolver::results_type _endpoints; /**< The endpoints found by the resolver */
        TSQueue<ByteBuffer> _sendQueue; /**< The queue of data to send */
        bool _asyncRun; /**< True if the asyncRun was called */
        std::thread _runThread; /**< The thread of the ioContext */

        explicit UDPClient(const std::shared_ptr<PacketRegistry> &packetRegistry);

        void asyncSend();

        void asyncRead();

        void handlePacketData(std::uint16_t packetId, ByteBuffer &buffer);
    };
} // namespace sa

#endif // SATURNITY_UDPCLIENT_HPP
