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
    class TCPServer;

    /**
     * @brief Class representing a asio tcp connection to a client.
     */
    class TCPConnectionToClient
        : public ConnectionToClient,
          public std::enable_shared_from_this<TCPConnectionToClient> {
    public:
        /**
         * @brief Start the connection.
         */
        void start() override;

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

        /**
         * @brief Send a packet to the client.
         * @param packet the packet to send.
         */
        void send(const std::unique_ptr<AbstractPacket> &packet) override;

        /**
         * @brief Disconnect the client.
         */
        void disconnect() override;

        /**
         * @brief Disconnect the client.
         * @param reason the reason of the disconnection.
         */
        void disconnect(const std::string &reason) override;

        /**
         * @brief Get the socket of the client.
         * @return the socket of the client.
         */
        const boost::asio::ip::tcp::socket &getSocket() const;

        /**
         * @brief Get the endpoint of the client.
         * @return the endpoint of the client.
         */
        const boost::asio::ip::tcp::endpoint &getEndpoint() const;

        /**
         * @brief Get the send queue of the client.
         * @return the send queue of the client.
         */
        const TSQueue<ByteBuffer> &getSendQueue() const;

        /**
         * @brief Create a TCPConnectionToClient.
         * @param packetRegistry the packet registry of the server.
         * @param id the id of the client.
         * @param server the server.
         * @param socket the socket of the client.
         * @return the created TCPConnectionToClient.
         */
        static std::shared_ptr<ConnectionToClient> create(
            const std::shared_ptr<PacketRegistry> &packetRegistry, int id, const std::shared_ptr<TCPServer> &server, boost::asio::ip::tcp::socket &&socket)
        {
            return std::shared_ptr<TCPConnectionToClient>(new TCPConnectionToClient(packetRegistry, id, server, std::move(socket)));
        }

    private:
        std::shared_ptr<TCPServer> _tcpServer; /**< The server */
        boost::asio::ip::tcp::socket _socket; /**< The socket of the client */
        boost::asio::ip::tcp::endpoint _endpoint; /**< The endpoint of the client */
        TSQueue<ByteBuffer> _sendQueue; /**< The queue of data to send */

        /**
         * @brief Construct a new TCPConnection To Client object.
         * @param packetRegistry the packet registry.
         * @param id the id of the connection.
         * @server the server.
         * @param socket the socket of the client.
         */
        explicit TCPConnectionToClient(
            const std::shared_ptr<PacketRegistry> &packetRegistry, int id, const std::shared_ptr<TCPServer> &server, boost::asio::ip::tcp::socket socket);

        /**
         * @brief Async send data to the client.
         */
        void asyncSend();

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
    };
} // namespace sa

#endif // SATURNITY_TCPCONNECTION_TO_CLIENT_HPP
