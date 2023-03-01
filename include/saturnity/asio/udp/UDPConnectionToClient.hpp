//
// Created by Nico on 01/03/2023.
//

#ifndef SATURNITY_UDPCONNECTIONTOCLIENT_HPP
#define SATURNITY_UDPCONNECTIONTOCLIENT_HPP

#include "saturnity/asio/udp/AbstractUDPProtocol.hpp"
#include "saturnity/core/network/server/ConnectionToClient.hpp"
#include "saturnity/core/ThreadSafeQueue.hpp"
#include <boost/asio.hpp>

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    class UDPServer;

    /**
     * @brief Class representing a asio udp connection to a client.
     */
    class UDPConnectionToClient
        : public ConnectionToClient,
          public std::enable_shared_from_this<UDPConnectionToClient>,
          public AbstractUDPProtocol {
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
         * @brief Get the endpoint of the client.
         * @return the endpoint of the client.
         */
        const boost::asio::ip::udp::endpoint &getEndpoint() const;

        /**
         * @brief Get the send queue of the client.
         * @return the send queue of the client.
         */
        const TSQueue<ByteBuffer> &getSendQueue() const;

        /**
         * @brief Create a UDPConnectionToClient.
         * @param packetRegistry the packet registry of the server.
         * @param id the id of the client.
         * @param server the server.
         * @param socket the socket of the client.
         * @return the created UDPConnectionToClient.
         */
        static std::shared_ptr<ConnectionToClient> create(
            const std::shared_ptr<PacketRegistry> &packetRegistry, int id, const std::shared_ptr<UDPServer> &server, boost::asio::ip::udp::socket *socket,
            boost::asio::ip::udp::endpoint &clientEndpoint)
        {
            return std::shared_ptr<UDPConnectionToClient>(new UDPConnectionToClient(packetRegistry, id, server, socket, clientEndpoint));
        }

    private:
        std::shared_ptr<UDPServer> _udpServer; /**< The server */
        boost::asio::ip::udp::socket *_socket; /**< The socket of the server */
        boost::asio::ip::udp::endpoint _endpoint; /**< The endpoint of the client */
        TSQueue<ByteBuffer> _sendQueue; /**< The queue of data to send */

        /**
         * @brief Construct a new UDPConnection To Client object.
         * @param packetRegistry the packet registry.
         * @param id the id of the connection.
         * @server the server.
         * @param socket the socket of the client.
         */
        explicit UDPConnectionToClient(const std::shared_ptr<PacketRegistry> &packetRegistry, int id, const std::shared_ptr<UDPServer> &server,
                                       boost::asio::ip::udp::socket *socket, boost::asio::ip::udp::endpoint &clientEndpoint);

        /**
         * @brief Async send data to the client.
         */
        void asyncSend();
    };
} // namespace sa

#endif // SATURNITY_UDPCONNECTIONTOCLIENT_HPP
