/*
** EPITECH PROJECT, 2023
** TCPConnectionToClient.hpp
** File description:
** TCPConnectionToClient.hpp
*/

#ifndef SATURNITY_TCPCONNECTION_TO_CLIENT_HPP
#define SATURNITY_TCPCONNECTION_TO_CLIENT_HPP

#include "saturnity/core/network/server/ConnectionToClient.hpp"
#include "saturnity/core/ThreadSafeQueue.hpp"
#include <boost/asio.hpp>

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief Class representing a asio tcp connection to a client.
     */
    class TCPConnectionToClient
        : public ConnectionToClient,
          public std::enable_shared_from_this<TCPConnectionToClient> { // TODO: check if shared_from_this is needed
    public:
        explicit TCPConnectionToClient(const std::shared_ptr<PacketRegistry> &packetRegistry, int id, boost::asio::io_context &ioContext);

        /**
         * @brief Send data to the client.
         * @param buffer the data to send.
         * @deprecated use send(AbstractPacket &packet) instead.
         */
        void send(ByteBuffer &buffer) override;

        /**
         * @brief Send a packet to the client.
         * @param packet the packet to send.
         */
        void send(AbstractPacket &packet) override;

        /**
         * @brief Send a packet to the client.
         * @param packet the packet to send.
         */
        void send(const std::shared_ptr<AbstractPacket> &packet) override;

        void send(const std::unique_ptr<AbstractPacket> &packet) override;

        void disconnect() override;

        void disconnect(const std::string &reason) override;

    private:
        boost::asio::io_context &_ioContext; /**< The ioContext of the server */
        boost::asio::ip::tcp::socket _socket; /**< The socket of the client */
        boost::asio::ip::tcp::endpoint _endpoint; /**< The endpoint of the client */
        TSQueue<ByteBuffer> _sendQueue; /**< The queue of data to send */
    };
} // namespace sa

#endif // SATURNITY_TCPCONNECTION_TO_CLIENT_HPP
